#include "ModelClass.h"


ModelClass::ModelClass()
{
  m_Texture = nullptr;
  m_Mesh = nullptr;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* modelFilename, char* textureFilename)
{
  bool result;

  m_Mesh = MeshFactory::get().GetResource(modelFilename);
  
  // Load the texture for this model.
  m_Texture = TextureFactory::get().GetResource(textureFilename);

  return true;
}

void ModelClass::Shutdown()
{

  return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
  // Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
  m_Mesh->Render(deviceContext);
  return;
}

int ModelClass::GetIndexCount()
{
  return m_Mesh->GetIndexCount();
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
  return m_Texture->GetTexture();
}
