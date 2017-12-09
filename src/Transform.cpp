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
    m_worldPosition = { 0.0f, 0.0f, 0.0f };

    // Assign default values to the rotation
    m_worldRotation = { 0.0f, 0.0f, 0.0f };

    // Assign default values to the scale
    m_scale = 1.0f;
  }
}