#include "ColorMaterial.h"

const std::string ColorMaterial::colorMaterialType = "color";

ColorMaterial::ColorMaterial(const std::string& name, XMVECTOR diffuseColor, XMVECTOR specularColor, XMVECTOR selfIluminationColor, float specularPower, ColorMaterialSubType subType) : IMaterial(name)
{
  m_diffuseColor = diffuseColor;
  m_specularColor = specularColor;
  m_selfIluminationColor = selfIluminationColor;
  m_specularPower = specularPower;
  m_subType = subType;
}

ColorMaterial::~ColorMaterial()
{
}
