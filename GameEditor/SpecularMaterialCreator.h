#pragma once

#include "IMaterialCreator.h"
#include "TextureFactory.h"
#include "SpecularMaterial.h"

class SpecularMaterialCreator :
  public IMaterialCreator
{
public:
  SpecularMaterialCreator() { m_type = SpecularMaterial::specularMaterialType; };
  virtual ~SpecularMaterialCreator();
  virtual IMaterial* Get(const std::string& fileInStr, const std::string& fileName) override;
};

