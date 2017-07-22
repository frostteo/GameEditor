#pragma once
#include "BumpSpecMaterial.h"
class BumpSpecMapMaterial :
  public BumpSpecMaterial
{
public:
  Texture* m_specularMap;
  static const std::string bumpSpecMapMaterialType;
public:
  BumpSpecMapMaterial(const std::string& name, Texture* texture, Texture* normalMap, Texture* specularMap, float bumpDepth, XMVECTOR specularColor, float specularPower) : BumpSpecMaterial(name, texture, normalMap, bumpDepth, specularColor, specularPower)
  {
    m_specularMap = specularMap;
  }
  virtual ~BumpSpecMapMaterial();
  virtual const std::string& GetType() override { return BumpSpecMapMaterial::bumpSpecMapMaterialType; }
  virtual int GetTextureCount() override { return 3; }
};

