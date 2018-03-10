#include "SpecularMaterialCreator.h"
#include "Logger.h"

SpecularMaterialCreator::~SpecularMaterialCreator()
{
}

IMaterial* SpecularMaterialCreator::Get(const std::string& fileInStr, const std::string& fileName)
{
  if (!m_textureFactory)
    RUNTIME_ERROR("Texture factory was not initialized!");

  char input;
  std::string type;
  std::string texturePath;
  std::stringstream fileStrStream(fileInStr);
  float r, g, b, a;
  float specularPower;

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> type;

  if (type != m_type)
    RUNTIME_ERROR("It is not material with specular type");

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
  fileStrStream >> r >> g >> b >> a;

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> specularPower;

  Texture* texture = m_textureFactory->GetResource(texturePath);
  SpecularMaterial* material = new SpecularMaterial(fileName, texture, XMVectorSet(r, g, b, a), specularPower);
  return material;
}
