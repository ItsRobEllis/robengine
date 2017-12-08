// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

// Precompiled Header
#include "Stdafx.h"

// Class Header
#include "Entity.h"

namespace RobEng
{
  Entity::Entity(std::string _entityName, bool _isEnabled)
  {
    m_entityName = _entityName;
    m_isEntityEnabled = _isEnabled;
  }

  Entity::~Entity()
  {
    m_entityComponents.clear();
  }
}