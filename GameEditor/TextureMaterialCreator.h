#pragma once

#include "IMaterialCreator.h"
#include "TextureFactory.h"
#include "TextureMaterial.h"

class TextureMaterialCreator :
  public IMaterialCreator
{
public:
  TextureMaterialCreator() { m_type = TextureMaterial::textureMaterialType; };
  virtual ~TextureMaterialCreator();
  virtual IMaterial* Get(const std::string& fileInStr, const std::string& fileName) override;
};

