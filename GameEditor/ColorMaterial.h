#pragma once

#include <directxmath.h>
#include "IMaterial.h"

using namespace DirectX;

enum ColorMaterialSubType {
  ONLY_COLOR = 0,
  COLOR_SPECULAR = 1,
  COLOR_SPEC_SELFILUM = 2
};

class ColorMaterial : public IMaterial
{
public:
  static const std::string colorMaterialType;

  XMVECTOR m_diffuseColor;
  XMVECTOR m_specularColor;
  XMVECTOR m_selfIluminationColor;
  float m_specularPower;
  ColorMaterialSubType m_subType;
public:
  ColorMaterial(const std::string& name, XMVECTOR diffuseColor, XMVECTOR specularColor, XMVECTOR selfIluminationColor, float specularPower, ColorMaterialSubType subType);
  virtual ~ColorMaterial();
  virtual const std::string& GetType() override { return ColorMaterial::colorMaterialType; }
};
