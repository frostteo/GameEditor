#include "SpecularMaterialCreator.h"


SpecularMaterialCreator::~SpecularMaterialCreator()
{
}

IMaterial* SpecularMaterialCreator::Get(const std::string& fileInStr, const std::string& fileName)
{
  if (!m_textureFactory)
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("Texture factory was not initialized!", __FILE__, __LINE__));

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
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("It is not material with specular type", __FILE__, __LINE__));

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
