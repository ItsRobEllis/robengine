// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

/// @brief Material class cpp file
/// Modified from :-
/// Dr Leigh McLoughlin (January 11th, 2017). OBJ Loader Code [online].
/// [Accessed 2017] Available from: https://mybu.bournemouth.ac.uk/bbcswebdav/pid-1368354-dt-content-rid-6146560_2/xid-6146560_2

// Precompiled Header
#include "Stdafx.h"

// Class Header
#include "Material.h"

namespace RobEng
{
  Material::Material()
  {
    // Initialise everything here
    _shaderModelMatLocation = 0;
    _shaderViewMatLocation = 0;
    _shaderProjMatLocation = 0;

    _shaderDiffuseColLocation = 0;
    _shaderEmissiveColLocation = 0;
    _shaderWSLightPosLocation = 0;
    _shaderSpecularColLocation = 0;

    _shaderTex1SamplerLocation = 0;

    _texture1 = 0;
  }

  Material::~Material()
  {
    // Clean up everything here
  }

  bool Material::LoadShaders(std::string _vertFilename, std::string _fragFilename)
  {
    std::weak_ptr<Core> m_core;

    std::ifstream _vertFile(_vertFilename);
    char *_vShaderText = NULL;

    if (_vertFile.is_open())
    {
      // Find out how many characters are in the file
      _vertFile.seekg(0, _vertFile.end);
      int _length = (int)_vertFile.tellg();
      _vertFile.seekg(0, _vertFile.beg);

      // Create our buffer
      _vShaderText = new char[_length];

      // Transfer data from file to buffer
      _vertFile.read(_vShaderText, _length);

      // Check it reached the end of the file
      if (!_vertFile.eof())
      {
        _vertFile.close();
        m_core.lock()->logMsg("WARNING: could not read vertex shader from file: " + _vertFilename, Core::SEVERE);
        return false;
      }

      // Find out how many characters were actually read
      _length = (int)_vertFile.gcount();

      // Needs to be NULL-terminated
      _vShaderText[_length - 1] = 0;

      _vertFile.close();
    }
    else
    {
      m_core.lock()->logMsg("WARNING: could not open vertex shader from file: " + _vertFilename, Core::SEVERE);
      return false;
    }

    std::ifstream _fragFile(_fragFilename);
    char *_fShaderText = NULL;

    if (_fragFile.is_open())
    {
      // Find out how many characters are in the file
      _fragFile.seekg(0, _fragFile.end);
      int _length = (int)_fragFile.tellg();
      _fragFile.seekg(0, _fragFile.beg);

      // Create our buffer
      _fShaderText = new char[_length];

      // Transfer data from file to buffer
      _fragFile.read(_fShaderText, _length);

      // Check it reached the end of the file
      if (!_fragFile.eof())
      {
        _fragFile.close();
        m_core.lock()->logMsg("WARNING: could not read fragment shader from file: " + _fragFilename, Core::SEVERE);
        return false;
      }

      // Find out how many characters were actually read
      _length = (int)_fragFile.gcount();

      // Needs to be NULL-terminated
      _fShaderText[_length - 1] = 0;

      _fragFile.close();
    }
    else
    {
      m_core.lock()->logMsg("WARNING: could not open fragment shader from file: " + _fragFilename, Core::SEVERE);
      return false;
    }

    // The 'program' stores the shaders
    _shaderProgram = glCreateProgram();

    // Create the vertex shader
    GLuint _vShader = glCreateShader(GL_VERTEX_SHADER);
    // Give GL the source for it
    glShaderSource(_vShader, 1, &_vShaderText, NULL);
    // Delete buffer
    delete[] _vShaderText;
    // Compile the shader
    glCompileShader(_vShader);
    // Check it compiled and give useful output if it didn't work!
    if (!CheckShaderCompiled(_vShader))
    {
      m_core.lock()->logMsg("ERROR: failed to compile vertex shader", Core::SEVERE);
      return false;
    }
    // This links the shader to the program
    glAttachShader(_shaderProgram, _vShader);

    // Same for the fragment shader
    GLuint _fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fShader, 1, &_fShaderText, NULL);
    // Delete buffer
    delete[] _fShaderText;
    glCompileShader(_fShader);
    if (!CheckShaderCompiled(_fShader))
    {
      m_core.lock()->logMsg("ERROR: failed to compile fragment shader", Core::SEVERE);
      return false;
    }
    glAttachShader(_shaderProgram, _fShader);

    // This makes sure the vertex and fragment shaders connect together
    glLinkProgram(_shaderProgram);
    // Check this worked
    GLint _linked;
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &_linked);
    if (!_linked)
    {
      GLsizei _len;
      glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &_len);

      GLchar* _log = new GLchar[_len + 1];
      glGetProgramInfoLog(_shaderProgram, _len, &_len, _log);
      m_core.lock()->logMsg("ERROR: Shader linking failed: " + (std::string)_log, Core::SEVERE);
      delete[] _log;

      return false;
    }

    // We will define matrices which we will send to the shader
    // To do this we need to retrieve the locations of the shader's matrix uniform variables
    glUseProgram(_shaderProgram);
    _shaderModelMatLocation = glGetUniformLocation(_shaderProgram, "modelMat");
    _shaderInvModelMatLocation = glGetUniformLocation(_shaderProgram, "invModelMat");
    _shaderViewMatLocation = glGetUniformLocation(_shaderProgram, "viewMat");
    _shaderProjMatLocation = glGetUniformLocation(_shaderProgram, "projMat");

    _shaderDiffuseColLocation = glGetUniformLocation(_shaderProgram, "diffuseColour");
    _shaderEmissiveColLocation = glGetUniformLocation(_shaderProgram, "emissiveColour");
    _shaderSpecularColLocation = glGetUniformLocation(_shaderProgram, "specularColour");
    _shaderWSLightPosLocation = glGetUniformLocation(_shaderProgram, "worldSpaceLightPos");

    _shaderTex1SamplerLocation = glGetUniformLocation(_shaderProgram, "tex1");

    return true;
  }

  bool Material::CheckShaderCompiled(GLint shader)
  {
    std::weak_ptr<Core> m_core;

    GLint _compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &_compiled);
    if (!_compiled)
    {
      GLsizei _len;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &_len);

      // OpenGL will store an error message as a string that we can retrieve and print
      GLchar* _log = new GLchar[_len + 1];
      glGetShaderInfoLog(shader, _len, &_len, _log);
      m_core.lock()->logMsg("ERROR: Shader compilation failed: " + (std::string)_log, Core::SEVERE);
      delete[] _log;

      return false;
    }
    return true;
  }

  unsigned int Material::LoadTexture(std::string _filename)
  {
    std::weak_ptr<Core> m_core;

    // Load SDL surface
    SDL_Surface *_image = SDL_LoadBMP(_filename.c_str());

    if (!_image) // Check it worked
    {
      m_core.lock()->logMsg("WARNING: could not load BMP image: " + _filename, Core::SEVERE);
      return 0;
    }

    // Create OpenGL texture
    unsigned int _texName = 0;
    glGenTextures(1, &_texName);


    glBindTexture(GL_TEXTURE_2D, _texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // By default, OpenGL mag filter is linear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // By default, OpenGL min filter will use mipmaps
    // We therefore either need to tell it to use linear or generate a mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // SDL loads images in BGR order
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image->w, _image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, _image->pixels);

    //glGenerateMipmap(GL_TEXTURE_2D);

    SDL_FreeSurface(_image);

    //glBindTexture(GL_TEXTURE_2D, 0);


    return _texName;
  }

  void Material::SetMatrices(glm::mat4 _modelMatrix, glm::mat4 _invModelMatrix, glm::mat4 _viewMatrix, glm::mat4 _projMatrix)
  {
    glUseProgram(_shaderProgram);
    // Send matrices and uniforms
    glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(_modelMatrix));
    glUniformMatrix4fv(_shaderInvModelMatLocation, 1, GL_TRUE, glm::value_ptr(_invModelMatrix));
    glUniformMatrix4fv(_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(_viewMatrix));
    glUniformMatrix4fv(_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(_projMatrix));
  }


  void Material::Apply()
  {
    glUseProgram(_shaderProgram);

    glUniform4fv(_shaderWSLightPosLocation, 1, glm::value_ptr(_lightPosition));

    glUniform3fv(_shaderEmissiveColLocation, 1, glm::value_ptr(_emissiveColour));
    glUniform3fv(_shaderDiffuseColLocation, 1, glm::value_ptr(_diffuseColour));
    glUniform3fv(_shaderSpecularColLocation, 1, glm::value_ptr(_specularColour));

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(_shaderTex1SamplerLocation, 0);
    glBindTexture(GL_TEXTURE_2D, _texture1);
  }
}