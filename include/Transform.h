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
    void WorldPosition(float _x, float _y, float _z) { m_worldPosition = { _x, _y, _z }; }

    // To change the rotation of the component
    void WorldRotation(float _x, float _y, float _z) { m_worldRotation = { _x, _y, _z }; }

    // To set the scale of the component
    void WorldScale(float _sc) { m_scale = _sc; }

    // Fetch the position of the component
    glm::vec3 WorldPosition(void) { return m_worldPosition; };

    // Fetch the rotation of the component
    glm::vec3 WorldRotation(void) { return m_worldRotation; };

    // Fetch the scale of the component
    float WorldScale(void) { return m_scale; };

  protected:

  private:
    // Position of the entity
    glm::vec3 m_worldPosition;

    // Rotation of the entity
    glm::vec3 m_worldRotation;

    // The scale of the entity
    float m_scale;
  };
}

#endif