#include "StaticGameObject.h"
#include "Model.h"

void StaticGameObject::SetModel(const Model* model)
{
  m_model = model;
  RebuildBBInWorldCoord();
}

void StaticGameObject::RebuildBBInWorldCoord() const
{
  const BoundingBox* modelBB = this->GetModel()->GetBoundingBox();
  XMFLOAT3 modelBBMinPoint = modelBB->GetMinPoint();
  XMFLOAT3 modelBBMaxPoint = modelBB->GetMaxPoint();
  XMMATRIX worldMatrix;
  this->GetWorldMatrix(worldMatrix);

  m_bbInWorldCoord.Initialize(modelBBMinPoint.x, modelBBMinPoint.y, modelBBMinPoint.z, modelBBMaxPoint.x, modelBBMaxPoint.y, modelBBMaxPoint.z, worldMatrix);
}
