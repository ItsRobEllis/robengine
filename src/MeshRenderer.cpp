// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

// Precompiled Header
#include "Stdafx.h"

// Header file
#include "MeshRenderer.h"

namespace RobEng
{
  MeshRenderer::MeshRenderer() {}

  MeshRenderer::~MeshRenderer() {}

  void MeshRenderer::Start()
  {

  }

  void MeshRenderer::Destroy()
  {

  }

  void MeshRenderer::Render()
  {
    std::weak_ptr<Mesh> _mesh;
    std::weak_ptr<Transform> _transform;

    if (_transform.expired())
    {
      m_core.lock()->logMsg("Failed to find Transform", Core::SEVERE);
      return;
    }

    if (_mesh.expired())
    {
      m_core.lock()->logMsg("Failed to find Mesh", Core::SEVERE);
      return;
    }

    glm::mat4 _viewMat = glm::inverse(_transform.lock()->TransformationMatrix(
      _transform.lock()->m_attachedEntity.lock()->getComponent<Transform>().lock()->LocalPosition(),
      _transform.lock()->m_attachedEntity.lock()->getComponent<Transform>().lock()->LocalRotation(),
      glm::vec3(1, 1, 1) * glm::vec3(1, 1, -1)
    ));

    glm::mat4 _modelMat = _transform.lock()->TransformationMatrix(
      _transform.lock()->LocalPosition(),
      _transform.lock()->LocalRotation(),
      glm::vec3(1, 1, 1) * glm::vec3(1, 1, 1)
    );

    for (size_t i = 0; i < (_mesh.lock()->GetVerts() / 3); i++)
    {
      std::weak_ptr<Material> _material; //= get loaded material
    }
  }
}