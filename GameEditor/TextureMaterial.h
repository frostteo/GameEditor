#pragma once
#include "IMaterial.h"
#include "Texture.h"

class TextureMaterial :
  public IMaterial
{
private:
  static const int TEXTURE_COUNT = 1;
  ID3D11ShaderResourceView* textures[TEXTURE_COUNT];
public:
  Texture* m_texture;
  static const std::string textureMaterialType;
public:
  TextureMaterial(const std::string& name, Texture* texture) : IMaterial(name) { m_texture = texture; textures[0] = m_texture->GetTexture(); }
  virtual ~TextureMaterial();
  virtual const std::string& GetType() override { return TextureMaterial::textureMaterialType; }
  virtual ID3D11ShaderResourceView** GetTextures() override { return textures; }
  virtual int GetTexturesCount() override { return TEXTURE_COUNT; }
};

