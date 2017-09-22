#pragma once

#include "IMaterialCreator.h"
#include "TextureFactory.h"
#include "BumpMaterial.h"
#include "Utils.h"

class BumpMaterialCreator :
  public IMaterialCreator
{
public:
  BumpMaterialCreator() { m_type = BumpMaterial::bumpMaterialType; }
  virtual ~BumpMaterialCreator();
  virtual IMaterial* Get(const std::string& fileInStr, const std::string& fileName) override;
};

