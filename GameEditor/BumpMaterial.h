#pragma once
#include "TextureMaterial.h"
class BumpMaterial :
  public TextureMaterial
{
public:
  Texture* m_normalMap;
  static const std::string bumpMaterialType;
  float m_bumpDepth;
public:
  BumpMaterial(const std::string& name, Texture* texture, Texture* normalMap, float bumpDepth)
    : TextureMaterial(name, texture)
  {
    m_normalMap = normalMap; m_bumpDepth = bumpDepth;
  }
  virtual ~BumpMaterial();
  virtual const std::string& GetType() override { return BumpMaterial::bumpMaterialType; }
  virtual int GetTextureCount() { return 2; }
};

