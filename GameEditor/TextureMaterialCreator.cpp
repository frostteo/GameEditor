#include "TextureMaterialCreator.h"
#include "Logger.h"

TextureMaterialCreator::~TextureMaterialCreator()
{
}

IMaterial* TextureMaterialCreator::Get(const std::string& fileInStr, const std::string& fileName)
{
  if (!m_textureFactory)
    RUNTIME_ERROR("Texture factory was not initialized!");

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
    RUNTIME_ERROR("It is not material with texture type");

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  std::getline(fileStrStream, texturePath);
  texturePath = Utils::Trim(texturePath);

  Texture* texture = m_textureFactory->GetResource(texturePath);
  TextureMaterial* material = new TextureMaterial(fileName, texture);
  return material;
}