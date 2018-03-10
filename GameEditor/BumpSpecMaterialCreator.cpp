#include "BumpSpecMaterialCreator.h"
#include "Logger.h"

BumpSpecMaterialCreator::~BumpSpecMaterialCreator()
{
}

IMaterial* BumpSpecMaterialCreator::Get(const std::string& fileInStr, const std::string& fileName)
{
  if (!m_textureFactory)
    RUNTIME_ERROR("Texture factory was not initialized!");

  char input;
  std::string type;
  std::string texturePath;
  std::string normalMapPath;
  std::stringstream fileStrStream(fileInStr);
  float bumpDepth;
  float rSpec, gSpec, bSpec, aSpec;
  float specularPower;

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

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> rSpec >> gSpec >> bSpec >> aSpec;

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> specularPower;

  Texture* texture = m_textureFactory->GetResource(texturePath);
  Texture* normalMap = m_textureFactory->GetResource(normalMapPath);
 BumpSpecMaterial* material = new BumpSpecMaterial(fileName, texture, normalMap, bumpDepth, XMFLOAT3(rSpec, gSpec, bSpec), specularPower);
  return material;
}
