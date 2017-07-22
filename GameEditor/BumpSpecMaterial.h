#pragma once

#include "BumpMaterial.h"
#include <directxmath.h>
#include "TextureMaterial.h"

using namespace DirectX;

class BumpSpecMaterial :
  public BumpMaterial
{
public:
  XMVECTOR m_specularColor;
  float m_specularPower;
  static const std::string bumpSpecMaterialType;
public:
  BumpSpecMaterial(const std::string& name, Texture* texture, Texture* normalMap, float bumpDepth, XMVECTOR specularColor, float specularPower)
    : BumpMaterial(name, texture, normalMap, bumpDepth)
  {
    m_specularColor = specularColor;
    m_specularPower = specularPower;
  }
  virtual ~BumpSpecMaterial();
  virtual const std::string& GetType() override { return BumpSpecMaterial::bumpSpecMaterialType; }
  virtual int GetTextureCount() override { return 2; }
};

