#pragma once

#include "BumpSpecDefferedShader.h"
#include "BumpSpecMapMaterial.h"

class BumpSpecMapDefferedShader :
  public BumpSpecDefferedShader
{
public:
  BumpSpecMapDefferedShader();
  virtual ~BumpSpecMapDefferedShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition) override;
};

