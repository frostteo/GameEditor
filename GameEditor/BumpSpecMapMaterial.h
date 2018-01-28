#pragma once
#include "BumpSpecMaterial.h"
class BumpSpecMapMaterial :
  public BumpSpecMaterial
{
private:
  static const int TEXTURE_COUNT = 3;
  ID3D11ShaderResourceView* textures[TEXTURE_COUNT];
public:
  Texture* m_specularMap;
  static const std::string bumpSpecMapMaterialType;
public:
  BumpSpecMapMaterial(const std::string& name, Texture* texture, Texture* normalMap, Texture* specularMap, float bumpDepth, XMFLOAT3 specularColor, float specularPower) : BumpSpecMaterial(name, texture, normalMap, bumpDepth, specularColor, specularPower)
  {
    m_specularMap = specularMap;
    textures[0] = m_texture->GetTexture();
    textures[1] = m_normalMap->GetTexture();
    textures[2] = m_specularMap->GetTexture();
  }
  virtual ~BumpSpecMapMaterial();
  virtual const std::string& GetType() override { return BumpSpecMapMaterial::bumpSpecMapMaterialType; }
  virtual int GetTexturesCount() override { return TEXTURE_COUNT; }
};

