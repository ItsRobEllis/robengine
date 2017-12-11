// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

#ifndef  _MESHRENDERER_H_
#define _MESHRENDERER_H_

// Precompiled Header
#include "Stdafx.h"

// Parent class
#include "Component.h"

namespace RobEng
{
  class Entity;
  class Mesh;
  class Material;
  class MeshRenderer : public Component
  {
  public:
    MeshRenderer();
    ~MeshRenderer();

    void Start();
    void Destroy();

    void Render();

    // This is the entity the component is attached to
    std::weak_ptr<Entity> m_attachedEntity;

    // Instance of Core for logging messages
    std::weak_ptr<Core> m_core;

  private:
    // Store an instance of mesh in a shared_ptr
    std::shared_ptr<Mesh> m_mesh;
    // Store an instance of material in a shared_ptr
    std::shared_ptr<Material> m_material;
  };
}

#endif
