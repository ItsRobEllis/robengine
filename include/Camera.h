// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

#ifndef _CAMERA_H_
#define _CAMERA_H_

// Precompiled Header
#include "Stdafx.h"

// Parent class
#include "Component.h"

namespace RobEng
{
  class Transform;
  class Entity;
  class Camera : public Component
  {
  public:
    // Constructor
    Camera();
    // Destructor
    ~Camera();

    void Start();

    // This is the entity the component is attached to
    std::weak_ptr<Entity> m_attachedEntity;

  protected:

  private:
    glm::vec3 m_cameraTarget;
    glm::mat4 m_projection = glm::perspective(75.0f, Core::getAspectRatio(), 0.01f, 1000.0f);

    glm::mat4 m_view = glm::lookAt(
      m_attachedEntity.lock()->getComponent<Transform>().lock()->LocalPosition(),
      m_cameraTarget,
      glm::vec3(0, 1, 0)
    );
  };
}

#endif