#pragma once

#include "GameObject.h"

class GridObject : public GameObject
{
public:
  GridObject();
  virtual ~GridObject();

  virtual void PrepareToRender(ID3D11DeviceContext* deviceContext) = 0;
  virtual void GetWorldMatrix(XMMATRIX& worldMatrix) { GameObject::GetWorldMatrix(worldMatrix); }
  virtual int GetIndexCount() = 0;
};

