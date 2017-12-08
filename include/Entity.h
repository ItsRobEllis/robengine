// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

#ifndef _ENTITY_H_
#define _ENTITY_H_

// Precompiled Header
#include "Stdafx.h"

// Placing everything under the RobEng namespace ensures there are no name conflicts
namespace RobEng
{
  class Component; // Forward declaring Component.h
  class Entity 
  {
  public:
    // Constructors
    Entity(std::string _entityName, bool _isEnabled);

    // Destructors
    ~Entity();
    
  protected:

  private:
    // The name of the entity
    std::string m_entityName;

    // Whether the entity is enabled (i.e. visible)
    bool m_isEntityEnabled;

    // A vector of shared_ptrs that contains all components added to this entity
    std::vector<std::shared_ptr<Component>> m_entityComponents;
  };
}

#endif