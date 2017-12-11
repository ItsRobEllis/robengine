// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

/// @brief Mesh class header file
/// Modified from :-
/// Dr Leigh McLoughlin (January 11th, 2017). OBJ Loader Code [online].
/// [Accessed 2017] Available from: https://mybu.bournemouth.ac.uk/bbcswebdav/pid-1368354-dt-content-rid-6146560_2/xid-6146560_2

#ifndef _MESH_H_
#define _MESH_H_

// Precompiled Header
#include "Stdafx.h"

namespace RobEng
{
  class Mesh
  {
  public:
    // Constructor
    Mesh();
    // Destructor
    ~Mesh();

    // Importer for the OBJ file
    void ImportOBJ(std::string _pathToFile);

    // Requires shaders
    void DrawMesh();

    int GetVerts(void) { return _vertexCount; }

  protected:

  private:
    // OpenGL Vertex Array Object
    GLuint _VertArrayObject;

    // Total amount of vertices in the mesh
    unsigned int _vertexCount;
  };
}

#endif