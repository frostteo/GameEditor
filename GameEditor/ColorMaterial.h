#pragma once

#include <directxmath.h>
#include "IMaterial.h"
#include "ColorMaterialSubType.h"

using namespace DirectX;

class ColorMaterial : public IMaterial
{
public:
  static const std::string colorMaterialType;

  XMVECTOR m_diffuseColor;
  XMVECTOR m_specularColor;
  XMVECTOR m_selfIluminationColor;
  float m_specularPower;
  float m_opacity;
  ColorMaterialSubType m_subType;
public:
  ColorMaterial(const std::string& name, XMVECTOR diffuseColor, XMVECTOR specularColor, XMVECTOR selfIluminationColor, float specularPower, float opacity, ColorMaterialSubType subType);
  virtual ~ColorMaterial();
  virtual const std::string& GetType() override { return ColorMaterial::colorMaterialType; }
};
