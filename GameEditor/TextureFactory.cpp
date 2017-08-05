#include "TextureFactory.h"


TextureFactory::TextureFactory()
{
}


TextureFactory::~TextureFactory()
{
}

TextureFactory* TextureFactory::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
  Shutdown();
  m_device = device;
  m_deviceContext = deviceContext;
  return this;
}

Texture* TextureFactory::GetNewResource(const std::string& filename)
{
  Texture* newTexture = new Texture();
  newTexture->Initialize(m_device, m_deviceContext, filename);
  return newTexture;
}
