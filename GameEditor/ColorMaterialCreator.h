#pragma once

#include "IMaterialCreator.h"
#include "ColorMaterial.h"

class ColorMaterialCreator :
  public IMaterialCreator
{
public:
  ColorMaterialCreator() { m_type = ColorMaterial::colorMaterialType; };
  virtual ~ColorMaterialCreator();
  virtual IMaterial* Get(const std::string& fileInStr, const std::string& fileName) override;
};

