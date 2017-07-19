#include "TextureMaterialCreator.h"

TextureMaterialCreator::~TextureMaterialCreator()
{
}

IMaterial* TextureMaterialCreator::Get(const std::string& fileInStr, const std::string& fileName)
{
  char input;
  std::string type;
  std::string texturePath;
  std::stringstream fileStrStream(fileInStr);

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> type; 

  if (type != m_type)
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("It is not material with texture type", __FILE__, __LINE__));

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> texturePath;

  Texture* texture = TextureFactory::get().GetResource(texturePath);
  TextureMaterial* material = new TextureMaterial(fileName, texture);
  return material;
}