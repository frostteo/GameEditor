#pragma once
#include "IMaterial.h"
#include "Texture.h"

class TextureMaterial :
  public IMaterial
{
public:
  Texture* m_texture;
public:
  TextureMaterial(const std::string& name, const std::string& type, Texture* texture) : IMaterial(name, type) { m_texture = texture; }
  virtual ~TextureMaterial();
};

