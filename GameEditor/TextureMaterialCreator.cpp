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
  fileStrStream >> type; //TODO FHolod: При неверном типе выбросить исключение

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> texturePath;

  Texture* texture = TextureFactory::get().GetResource(texturePath);
  TextureMaterial* material = new TextureMaterial(fileName, type, texture);
  return material;
}