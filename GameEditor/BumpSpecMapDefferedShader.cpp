#include "BumpSpecMapDefferedShader.h"


BumpSpecMapDefferedShader::BumpSpecMapDefferedShader()
{
}


BumpSpecMapDefferedShader::~BumpSpecMapDefferedShader()
{
}

void BumpSpecMapDefferedShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
  XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition)
{
  BumpSpecMapMaterial* bumpMaterial = (BumpSpecMapMaterial*)material;

  SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, bumpMaterial->m_specularColor, bumpMaterial->m_specularPower, cameraPosition, bumpMaterial->m_bumpDepth);

  RenderShader(deviceContext, indexCount);
}