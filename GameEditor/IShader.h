#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include "IMaterial.h"
#include "Logger.h"
using namespace DirectX;

class IShader
{
public:
  IShader();
  virtual ~IShader();
  virtual bool Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material) = 0;
};

