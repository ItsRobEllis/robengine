/**
  * The Entity Class defines everything in an entity bar its components.
  * It is made up of an init and destroy function, as well as other details such as the entity's name, any components attached to it as well as whether it's enabled or not.
  * @file: Entity.cpp
  * @author: Rob Ellis
  * @date: 28/11/2017
  */

// Precompiled Header
#include "Stdafx.h"

// Class Header
#include "Entity.h"

namespace RobEng
{
  Entity::Entity()
  {}

  Entity::~Entity()
  {}

  void Entity::Init(std::string _entityName, bool _isEnabled)
  {
    m_entityName = _entityName;
    m_isEntityEnabled = _isEnabled;

    addComponent<Transform>();
  }

  void Entity::Destroy()
  {
    for (size_t i = 0; i < m_entityComponents.size(); i++)
    {
      m_entityComponents.at(i)->Destroy();
    }
  }
}