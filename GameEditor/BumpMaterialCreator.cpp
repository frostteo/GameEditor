#include "BumpMaterialCreator.h"
#include "Logger.h"

BumpMaterialCreator::~BumpMaterialCreator()
{
}

IMaterial* BumpMaterialCreator::Get(const std::string& fileInStr, const std::string& fileName)
{
  if (!m_textureFactory)
    RUNTIME_ERROR("Texture factory was not initialized!");

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
    RUNTIME_ERROR("It is not material with texture type");

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  std::getline(fileStrStream, texturePath);
  texturePath = Utils::Trim(texturePath);

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  std::getline(fileStrStream, normalMapPath);
  normalMapPath = Utils::Trim(normalMapPath);

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> bumpDepth;

  Texture* texture = m_textureFactory->GetResource(texturePath);
  Texture* normalMap = m_textureFactory->GetResource(normalMapPath);
  BumpMaterial* material = new BumpMaterial(fileName, texture, normalMap, bumpDepth);
  return material;
}
