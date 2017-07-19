#include "SpecularMaterial.h"

SpecularMaterial::SpecularMaterial(const std::string& name, Texture* texture, XMVECTOR specularColor, float specularPower)
  : TextureMaterial(name, texture)
{
  m_specularColor = specularColor;
  m_specularPower = specularPower;
}


SpecularMaterial::~SpecularMaterial()
{
}

const std::string SpecularMaterial::specularMaterialType = "specular";