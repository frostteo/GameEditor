#include "TextureMaterialCreator.h"

TextureMaterialCreator::~TextureMaterialCreator()
{
}

IMaterial* TextureMaterialCreator::Get(const std::string& fileInStr, const std::string& fileName)
{
  if (!m_textureFactory)
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("Texture factory was not initialized!", __FILE__, __LINE__));

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
  std::getline(fileStrStream, texturePath);
  texturePath = Utils::Trim(texturePath);

  Texture* texture = m_textureFactory->GetResource(texturePath);
  TextureMaterial* material = new TextureMaterial(fileName, texture);
  return material;
}