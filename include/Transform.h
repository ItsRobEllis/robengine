// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

// Precompiled Header
#include "Stdafx.h"

// Parent class
#include "Component.h"

namespace RobEng
{
  class Transform : public Component
  {
  public:
    // Constructors
    Transform();

    // Destructors
    ~Transform();
    
    // Start function to assign default location for all transform components
    void Start();
    
    // To change the position of the component
    void SetPosition(float _x, float _y, float _z) { m_positionX = _x; m_positionY = _y, m_positionZ = _z; }

    // To change the rotation of the component
    void SetRotation(float _x, float _y, float _z) { m_rotationX = _x; m_rotationY = _y, m_rotationZ = _z; }

    // To set the scale of the component
    void SetScale(float _sc) { m_scale = _sc; }

  protected:

  private:
    // Position of the entity
    float m_positionX,
          m_positionY,
          m_positionZ;

    // Rotation of the entity
    float m_rotationX,
          m_rotationY,
          m_rotationZ;

    float m_scale;
  };
}

#endif