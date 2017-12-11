// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

/// @brief Material class header file
/// Modified from :-
/// Dr Leigh McLoughlin (January 11th, 2017). OBJ Loader Code [online].
/// [Accessed 2017] Available from: https://mybu.bournemouth.ac.uk/bbcswebdav/pid-1368354-dt-content-rid-6146560_2/xid-6146560_2

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

// Precompiled Header
#include "Stdafx.h"

namespace RobEng
{
  class Material
  {
  public:
    Material();
    ~Material();

    // Loads shaders from file
    // Returns false if there was an error - it will also print out messages to console
    bool LoadShaders(std::string _vertFilename, std::string _fragFilename);

    // For setting the standard matrices needed by the shader
    void SetMatrices(glm::mat4 _modelMatrix, glm::mat4 _invModelMatrix, glm::mat4 _viewMatrix, glm::mat4 _projMatrix);

    // For setting material properties
    void SetEmissiveColour(glm::vec3 _input) { _emissiveColour = _input; }
    void SetDiffuseColour(glm::vec3 _input) { _diffuseColour = _input; }
    void SetSpecularColour(glm::vec3 _input) { _specularColour = _input; }

    // Set light position in world space
    void SetLightPosition(glm::vec3 _input) { _lightPosition = _input; }

    // Sets texture
    // This applies to ambient, diffuse and specular colours
    // If you want textures for anything else, you'll need to do that yourself ;)
    bool SetTexture(std::string _filename) { _texture1 = LoadTexture(_filename); return _texture1>0; }

    // Sets the material, applying the shaders
    void Apply();

  private:
    // Utility function
    bool CheckShaderCompiled(GLint _shader);

    // The OpenGL shader program handle
    int _shaderProgram;

    // Locations of Uniforms in the vertex shader
    int _shaderModelMatLocation;
    int _shaderInvModelMatLocation;
    int _shaderViewMatLocation;
    int _shaderProjMatLocation;

    // Location of Uniforms in the fragment shader
    int _shaderDiffuseColLocation, _shaderEmissiveColLocation, _shaderSpecularColLocation;
    int _shaderWSLightPosLocation;
    int _shaderTex1SamplerLocation;

    // Local store of material properties to be sent to the shader
    glm::vec3 _emissiveColour, _diffuseColour, _specularColour;
    glm::vec3 _lightPosition;

    // Loads a .bmp from file
    unsigned int LoadTexture(std::string _filename);

    // OpenGL handle for the texture
    unsigned int _texture1;

  };
}

#endif