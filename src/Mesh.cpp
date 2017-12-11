// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

/// @brief Mesh class cpp file
/// Modified from :-
/// Dr Leigh McLoughlin (January 11th, 2017). OBJ Loader Code [online].
/// [Accessed 2017] Available from: https://mybu.bournemouth.ac.uk/bbcswebdav/pid-1368354-dt-content-rid-6146560_2/xid-6146560_2

// Precompiled Header
#include "Stdafx.h"

// Class Header
#include "Mesh.h"

namespace RobEng
{
  Mesh::Mesh()
  {
    _VertArrayObject = 0;
    glGenVertexArrays(1, &_VertArrayObject);

    // Set the default value of _vertexCount to 0
    _vertexCount = 0;
  }

  Mesh::~Mesh()
  {
    glDeleteVertexArrays(1, &_VertArrayObject);
  }

  void Mesh::ImportOBJ(std::string _pathToFile)
  {
    std::weak_ptr<Core> m_core;

    // Search for the file
    std::ifstream _inputFile(_pathToFile);

    if (_inputFile.is_open())
    {
      std::vector<glm::vec2> _rawUVData;
      std::vector<glm::vec3> _rawPositionData;
      std::vector<glm::vec3> _rawNormalData;

      std::vector<glm::vec2> _orderedUVData;
      std::vector<glm::vec3> _orderedPositionData;
      std::vector<glm::vec3> _orderedNormalData;

      std::string _currentLine;

      while (std::getline(_inputFile, _currentLine))
      {
        std::stringstream _currentLineStream(_currentLine);
        //std::cout<< _currentLine <<std::endl;

        if (!_currentLine.substr(0, 2).compare(0, 2, "vt"))
        {
          std::string _junk;
          float x, y;
          _currentLineStream >> _junk >> x >> y;
          _rawUVData.push_back(glm::vec2(x, y));
        }
        else if (!_currentLine.substr(0, 2).compare(0, 2, "vn"))
        {
          std::string _junk;
          float x, y, z;
          _currentLineStream >> _junk >> x >> y >> z;
          _rawNormalData.push_back(glm::vec3(x, y, z));
        }
        else if (!_currentLine.substr(0, 2).compare(0, 1, "v"))
        {
          std::string _junk;
          float x, y, z;
          _currentLineStream >> _junk >> x >> y >> z;
          _rawPositionData.push_back(glm::vec3(x, y, z));
        }
        else if (!_currentLine.substr(0, 2).compare(0, 1, "f"))
        {
          std::string _junk;
          std::string _verts[4];

          _currentLineStream >> _junk >> _verts[0] >> _verts[1] >> _verts[2] >> _verts[3];

          if (_verts[3].empty())
          {
            for (unsigned int i = 0; i < 3; i++)
            {
              std::stringstream _currentSection(_verts[i]);

              // There is just position data
              unsigned int posID = 0;
              unsigned int uvID = 0;
              unsigned int normID = 0;

              if (_verts[i].find('/') == std::string::npos)
              {
                // No texcoords or normals
                _currentSection >> posID;
              }
              else if (_verts[i].find("//") != std::string::npos)
              {
                // No texcoords
                char _junk;
                _currentSection >> posID >> _junk >> _junk >> normID;
              }
              else
              {
                char _junk;
                _currentSection >> posID >> _junk >> uvID >> _junk >> normID;
              }

              if (posID > 0)
              {
                _orderedPositionData.push_back(_rawPositionData[posID - 1]);
              }
              if (uvID > 0)
              {
                _orderedUVData.push_back(_rawUVData[uvID - 1]);
              }
              if (normID > 0)
              {
                _orderedNormalData.push_back(_rawNormalData[normID - 1]);
              }

            }
          }
          else
          {
            m_core.lock()->logMsg("WARNING: This OBJ loader only works with triangles but a quad has been detected. Please triangulate your mesh.", Core::SEVERE);
            _inputFile.close();
            return;
          }

        }
      }

      _inputFile.close();

      _vertexCount = _orderedPositionData.size();

      if (_vertexCount > 0)
      {

        glBindVertexArray(_VertArrayObject);

        // Variable for storing a VBO
        GLuint _posBuffer = 0;
        // Create a generic 'buffer'
        glGenBuffers(1, &_posBuffer);
        // Tell OpenGL that we want to activate the buffer and that it's a VBO
        glBindBuffer(GL_ARRAY_BUFFER, _posBuffer);
        // With this buffer active, we can now send our data to OpenGL
        // We need to tell it how much data to send
        // We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertexCount * 3, &_orderedPositionData[0], GL_STATIC_DRAW);

        // This tells OpenGL how we link the vertex data to the shader
        // (We will look at this properly in the lectures)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        if (_orderedNormalData.size() > 0)
        {
          // Variable for storing a VBO
          GLuint normBuffer = 0;
          // Create a generic 'buffer'
          glGenBuffers(1, &normBuffer);
          // Tell OpenGL that we want to activate the buffer and that it's a VBO
          glBindBuffer(GL_ARRAY_BUFFER, normBuffer);
          // With this buffer active, we can now send our data to OpenGL
          // We need to tell it how much data to send
          // We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
          glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertexCount * 3, &_orderedNormalData[0], GL_STATIC_DRAW);

          // This tells OpenGL how we link the vertex data to the shader
          // (We will look at this properly in the lectures)
          glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
          glEnableVertexAttribArray(1);
        }


        if (_orderedUVData.size() > 0)
        {
          // Variable for storing a VBO
          GLuint _texBuffer = 0;
          // Create a generic 'buffer'
          glGenBuffers(1, &_texBuffer);
          // Tell OpenGL that we want to activate the buffer and that it's a VBO
          glBindBuffer(GL_ARRAY_BUFFER, _texBuffer);
          // With this buffer active, we can now send our data to OpenGL
          // We need to tell it how much data to send
          // We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
          glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertexCount * 2, &_orderedUVData[0], GL_STATIC_DRAW);

          // This tells OpenGL how we link the vertex data to the shader
          // (We will look at this properly in the lectures)
          glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
          glEnableVertexAttribArray(2);
        }

      }
    }
    else
    {
     m_core.lock()->logMsg("WARNING: File not found: " + _pathToFile, Core::SEVERE);
    }  
  }

  void Mesh::DrawMesh()
  {
    // Activate the VAO
    glBindVertexArray(_VertArrayObject);

    // Tell OpenGL to draw it
    // Must specify the type of geometry to draw and the number of vertices
    glDrawArrays(GL_TRIANGLES, 0, _vertexCount);

    // Unbind VAO
    glBindVertexArray(0);
  }
}