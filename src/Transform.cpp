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
    _X = 0;
    _Y = 0;
    _Z = 0;
  }
}