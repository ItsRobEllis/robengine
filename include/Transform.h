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
  class Entity;
  class Camera;
  class Transform : public Component
  {
  public:
    // Constructors
    Transform();

    // Destructors
    ~Transform();
    
    // Overflow start function to assign default location for all transform components
    void Start();

    // Overflow destroy function
    void Destroy();

    // Function to move the component
    void Translate(glm::vec3 _translation);

    // Function to rotate the component
    void Rotate(glm::vec3 _rotation);

    // To change the local position of the component
    void LocalPosition(glm::vec3 _newPosition);
    // To change the local rotation of the component
    void LocalRotation(glm::vec3 _newRotation);
    // To set the local scale of the component
    void LocalScale(glm::vec3 _newScale);

    // Fetch the local position of the component
    glm::vec3 LocalPosition(void) { return m_localPosition; };
    // Fetch the local rotation of the component
    glm::vec3 LocalRotation(void) { return m_localRotation; };
    // Fetch the local scale of the component
    glm::vec3 LocalScale(void)    { return m_localScale; };

    // Defines the parent of this transform component
    void SetParent(std::weak_ptr<Transform> _parent) { m_parent = _parent; }
    // Fetch the parent
    std::weak_ptr<Transform> GetParent(void) { return m_parent; }

  protected:

  private:
    // Local position of the transform component
    glm::vec3 m_localPosition;
    // Local rotation of the transform component
    glm::vec3 m_localRotation;   
    // Local scale of the entity
    glm::vec3 m_localScale;

    // Store a parent if a parent exists
    std::weak_ptr<Transform> m_parent;
  };
}

#endif