#pragma once
#include "TextureMaterial.h"
class BumpMaterial :
  public TextureMaterial
{
private:
  static const int TEXTURES_COUNT = 2;
  ID3D11ShaderResourceView* textures[TEXTURES_COUNT];
public:
  Texture* m_normalMap;
  static const std::string bumpMaterialType;
  float m_bumpDepth;
public:
  BumpMaterial(const std::string& name, Texture* texture, Texture* normalMap, float bumpDepth)
    : TextureMaterial(name, texture)
  {
    m_normalMap = normalMap;
    m_bumpDepth = bumpDepth;
    textures[0] = m_texture->GetTexture();
    textures[1] = m_normalMap->GetTexture();
  }
  virtual ~BumpMaterial();
  virtual const std::string& GetType() override { return BumpMaterial::bumpMaterialType; }
  virtual ID3D11ShaderResourceView** GetTextures() { return textures; }
  virtual int GetTexturesCount() { return TEXTURES_COUNT; }
};

