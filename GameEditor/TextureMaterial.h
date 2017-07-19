#pragma once
#include "IMaterial.h"
#include "Texture.h"

class TextureMaterial :
  public IMaterial
{
public:
  Texture* m_texture;
  static const std::string textureMaterialType;
public:
  TextureMaterial(const std::string& name, Texture* texture) : IMaterial(name) { m_texture = texture; }
  virtual ~TextureMaterial();
  virtual const std::string& GetType() override { return TextureMaterial::textureMaterialType; }
};

