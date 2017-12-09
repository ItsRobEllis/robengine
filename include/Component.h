// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

// Precompiled Header
#include "Stdafx.h"

// Placing everything under the RobEng namespace ensures there are no name conflicts
namespace RobEng
{
  class Entity;
  class Component
  {
  public:
    // Constructors
    Component();

    // Destructors
    ~Component();

    // Component Functions
    virtual void Awake();   // Awake
    virtual void Start();   // Start
    virtual void Update();  // Update
    virtual void Render();  // Render
    virtual void Destroy(); // Destroy

    // This is the entity the component is attached to
    std::weak_ptr<Entity> m_attachedEntity;

  protected:

  private:

  };
}

#endif