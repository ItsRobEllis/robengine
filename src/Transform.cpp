// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

// Precompiled Header
#include "Stdafx.h"

// Class Header
#include "Transform.h"

namespace RobEng
{
  Transform::Transform() {}

  Transform::~Transform() {}

  void Transform::Start()
  {
    // Assign defualt values to the position
    m_positionX = 0.0f;
    m_positionY = 0.0f;
    m_positionZ = 0.0f;

    // Assign default values to the rotation
    m_rotationX = 0.0f;
    m_rotationY = 0.0f;
    m_rotationZ = 0.0f;

    // Assign default values to the scale
    m_scale = 1.0f;
  }
}