#pragma once

#include <directxmath.h>
#include "TextureMaterial.h"

using namespace DirectX;

class SpecularMaterial :
  public TextureMaterial
{
public:
  XMVECTOR m_specularColor;
  float m_specularPower;
  static const std::string specularMaterialType;
public:
  SpecularMaterial(const std::string& name, Texture* texture, XMVECTOR specularColor, float specularPower);
  virtual ~SpecularMaterial();
  virtual const std::string GetType() const override { return SpecularMaterial::specularMaterialType; }
};

