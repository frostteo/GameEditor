#pragma once

#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

class GridObject
{
public:
  GridObject();
  virtual ~GridObject();

  virtual void PrepareToRender(ID3D11DeviceContext* deviceContext) = 0;
  virtual int GetIndexCount() = 0;
};

