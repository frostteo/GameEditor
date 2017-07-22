#pragma once

#include "IMaterialCreator.h"
#include "TextureFactory.h"
#include "BumpSpecMapMaterial.h"

class BumpSpecMapMaterialCreator :
  public IMaterialCreator
{
public:
  BumpSpecMapMaterialCreator() { m_type = BumpSpecMapMaterial::bumpSpecMapMaterialType; }
  virtual ~BumpSpecMapMaterialCreator();
  virtual IMaterial* Get(const std::string& fileInStr, const std::string& fileName) override;
};

