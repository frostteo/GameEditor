#pragma once

#include "IMaterialCreator.h"
#include "TextureFactory.h"
#include "BumpSpecMaterial.h"

class BumpSpecMaterialCreator :
  public IMaterialCreator
{
public:
  BumpSpecMaterialCreator() { m_type = BumpSpecMaterial::bumpSpecMaterialType; }
  virtual ~BumpSpecMaterialCreator();
  virtual IMaterial* Get(const std::string& fileInStr, const std::string& fileName) override;
};

