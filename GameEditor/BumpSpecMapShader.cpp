#include "BumpSpecMapShader.h"


BumpSpecMapShader::BumpSpecMapShader()
{
}


BumpSpecMapShader::~BumpSpecMapShader()
{
}

void BumpSpecMapShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
  XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition)
{
  BumpSpecMapMaterial* bumpMaterial = (BumpSpecMapMaterial*)material;
  ID3D11ShaderResourceView* textures[3];
  textures[0] = bumpMaterial->m_texture->GetTexture();
  textures[1] = bumpMaterial->m_normalMap->GetTexture();
  textures[2] = bumpMaterial->m_specularMap->GetTexture();

  SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, textures, bumpMaterial->GetTextureCount(), lightining->GetDirectLightDirection(), lightining->GetAmbientColor(), lightining->GetDirectLightColor(), bumpMaterial->m_specularColor, bumpMaterial->m_specularPower, cameraPosition, bumpMaterial->m_bumpDepth);

  RenderShader(deviceContext, indexCount);
}
