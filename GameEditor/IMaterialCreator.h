#pragma once

#include <string>
#include "IMaterial.h"
#include "TextureFactory.h"

class Logger;

class IMaterialCreator
{
protected:
  std::string m_type;
  TextureFactory* m_textureFactory = nullptr;
public:
  IMaterialCreator();
  virtual ~IMaterialCreator();
  bool CanCreate(const std::string& type) { return m_type == type; }
  virtual IMaterial* Get(const std::string& fileInStr, const std::string& fileName) {
    return nullptr;
  }
  IMaterialCreator* SetTextureFactory(TextureFactory* textureFactory) { m_textureFactory = textureFactory; return this; }
};

