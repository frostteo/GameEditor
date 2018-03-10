#include "BumpSpecMapShader.h"
#include "LightininigSystem.h"

BumpSpecMapShader::BumpSpecMapShader()
{
}


BumpSpecMapShader::~BumpSpecMapShader()
{
}

void BumpSpecMapShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
  XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, const XMFLOAT3& cameraPosition)
{
  BumpSpecMapMaterial* bumpMaterial = (BumpSpecMapMaterial*)material;

  SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, lightining->GetDirectLightDirection(), lightining->GetAmbientColor(), lightining->GetDirectLightColor(), bumpMaterial->m_specularColor, bumpMaterial->m_specularPower, cameraPosition, bumpMaterial->m_bumpDepth);

  RenderShader(deviceContext, indexCount);
}
