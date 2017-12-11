#ifndef _ENTITY_H_
#define _ENTITY_H_

/**
  * The Entity Class defines everything in an entity bar its components.
  * It is made up of an init and destroy function, as well as other details such as the entity's name, any components attached to it as well as whether it's enabled or not.
  * @file: Entity.h
  * @author: Rob Ellis
  * @date: 28/11/2017
  */

// Precompiled Header
#include "Stdafx.h"

// Placing everything under the RobEng namespace ensures there are no name conflicts
namespace RobEng
{
  class Component; // Forward declaring Component.h
  class Entity : public std::enable_shared_from_this<Entity>
  {
  public:
    // Constructor and init function
    Entity();
    void Init(std::string _entityName, bool _isEnabled);

    // Destructors and destroy function
    ~Entity();
    void Destroy();
   
  private:
    // The name of the entity
    std::string m_entityName;

    // Whether the entity is enabled (i.e. visible)
    bool m_isEntityEnabled;

    // A vector of shared_ptrs that contains all the components attached to this entity
    std::vector<std::shared_ptr<Component>> m_entityComponents;    
  
// ----------------------------------------------------------------------------------------------
// --- This public section in the Entity Class is specifically for storing template functions ---
// ----------------------------------------------------------------------------------------------

  public:
    // Getting a component from the entity
    template<class _T>
    std::weak_ptr<_T> getComponent()
    {
      for (size_t i = 0; i < m_entityComponents.size(); i++)
      {
        // Create a variable c that compares component type at index i against _T and stores the result
        std::weak_ptr<_T> c = std::dynamic_pointer_cast<_T>(m_entityComponents.at(i));

        // After defining c, see if it is still valid
        if (!c.expired())
        {
          return c;
        }
      }
      // Return null weakptr
      return{};
    }

    // Adding a component to the entity
    template<class _T>
    std::weak_ptr<_T> addComponent()
    {
      std::shared_ptr<_T> c = std::make_shared<_T>();

      m_entityComponents.push_back(c);
      c->m_attachedEntity = shared_from_this();
      c->Awake();

      return c;
    }
  };
};

#endif