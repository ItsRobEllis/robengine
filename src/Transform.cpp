// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

// Precompiled Header
#include "Stdafx.h"

// Class Header
#include "Transform.h"

namespace RobEng
{
  Transform::Transform() {}

  Transform::~Transform() {}

  void Transform::Start()
  {
    // Assign defualt values to the local position
    m_localPosition = { 0.0f, 0.0f, 0.0f };

    // Assign default values to the local rotation
    m_localRotation = { 0.0f, 0.0f, 0.0f };

    // Assign default values to the scale
    m_localScale = { 1.0f, 1.0f, 1.0f };

    // Set the default parent to nullptr
    m_parent.lock() = nullptr;
  }

  void Transform::Destroy()
  {
    m_parent.lock() = nullptr;
  }

  // Function to move the component in world space
  void Transform::Translate(glm::vec3 _translation)
  {
    m_localPosition = m_localPosition += _translation;
  }

  // Function to rotate the component in world space
  void Transform::Rotate(glm::vec3 _rotation)
  {
    m_localRotation = m_localRotation += _rotation;
  }

  // To change the local position of the component
  void Transform::LocalPosition(glm::vec3 _newPosition) 
  {
    // TODO ALL THIS
    /*if (!m_parent.expired())
    {
      glm::mat4x4 _trs;
      std::weak_ptr<Transform> _trans = GetParent();

      while (!_trans.expired())
      {
        //_trs = glm::mat4x4::
      }
    }
    else
    {*/
      m_localPosition = _newPosition;
    //}
  }

  // To change the local rotation of the component
  void Transform::LocalRotation(glm::vec3 _newRotation)
  {
    m_localRotation = _newRotation;
  }

  // To set the local scale of the component
  void Transform::LocalScale(glm::vec3 _newScale)
  {
    m_localScale = _newScale;
  }

  glm::mat4 Transform::TransformationMatrix(glm::vec3 _translation, glm::vec3 _rotation, glm::vec3 _scale)
  {
    // Create a Matrix4 to store the result
    glm::mat4 _result;

    // Apply the translation
    _result = glm::translate(_result, _translation);

    // Apply the rotation Y
    _result = glm::rotate(_result, _rotation.y, glm::vec3(0.f, 1.f, 0.f));
    // Apply the rotation Z
    _result = glm::rotate(_result, _rotation.z, glm::vec3(0.f, 0.f, 1.f));
    // Apply the rotation X
    _result = glm::rotate(_result, _rotation.x, glm::vec3(1.f, 0.f, 0.f));

    // Apply the scale
    _result = glm::scale(_result, _scale);

    // Return the transformation matrix
    return _result;
  }
}