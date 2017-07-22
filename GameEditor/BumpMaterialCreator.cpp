#include "BumpMaterialCreator.h"

BumpMaterialCreator::~BumpMaterialCreator()
{
}

IMaterial* BumpMaterialCreator::Get(const std::string& fileInStr, const std::string& fileName)
{
  char input;
  std::string type;
  std::string texturePath;
  std::string normalMapPath;
  std::stringstream fileStrStream(fileInStr);
  float bumpDepth;

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

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> normalMapPath;

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> bumpDepth;

  Texture* texture = TextureFactory::get().GetResource(texturePath);
  Texture* normalMap = TextureFactory::get().GetResource(normalMapPath);
  BumpMaterial* material = new BumpMaterial(fileName, texture, normalMap, bumpDepth);
  return material;
}