#include "Static.h"


Static::Static()
{
  m_material = nullptr;
  m_mesh = nullptr;
}


Static::~Static()
{
}

void Static::SetMaterial(IMaterial* material, ShaderFactory* shaderFactory)
{
  m_material = material;
  InitializeShader(shaderFactory);
}

void Static::SetMesh(Mesh* mesh)
{
  m_mesh = mesh;
}

void Static::InitializeShader(ShaderFactory* shaderFactory)
{
  m_shader = shaderFactory->Get(m_material->GetType());
}

void Static::Render(ID3D11DeviceContext* deviceContext, XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix, LightininigSystem* lightining, XMFLOAT3& cameraPostion)
{
  m_mesh->Render(deviceContext);

  XMMATRIX worldMatrix;
  this->GetWorldMatrix(worldMatrix);
  m_shader->Render(deviceContext, m_mesh->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_material, lightining, cameraPostion);
}