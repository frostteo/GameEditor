#pragma once

#include <d3d11.h>
#include "Texture.h"
#include "Singleton.h"
#include "SharedResourcesFactory.h"

class TextureFactory : public SharedResourcesFactory<Texture>
{
private:
  ID3D11Device* m_device;
  ID3D11DeviceContext* m_deviceContext;
  std::string m_pathToTextures;
protected:
  Texture* GetNewResource(const std::string& filename) override;
public:
  TextureFactory* Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string pathToTextures);
  TextureFactory();
  virtual ~TextureFactory();
};

