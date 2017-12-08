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
    void Awake();   // Awake
    void Start();   // Start
    void Update();  // Update
    void Render();  // Render
    void Destroy(); // Destroy

    // This is the entity the component is attached to
    std::shared_ptr<Entity> m_attachedEntity;

  protected:

  private:

  };
}

#endif