// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

// Precompiled Header
#include "Stdafx.h"

// Class Header
#include "Component.h"

namespace RobEng
{
  // These constructors and destructors are empty and no variables need defining
  Component::Component() {}
  Component::~Component() {}

  // These functions are empty, as they are instead filled up inside each child Component type

  // This function is triggered when the component is first created and the entity wakes up
  void Component::Awake() {}

  // This occurs on the first update
  void Component::Start() {}

  // This occurs on every update
  void Component::Update() {}

  // This occurs when the application enters its render function
  void Component::Render() {}

  // This occurs when the component is destroyed
  void Component::Destroy() {}
}