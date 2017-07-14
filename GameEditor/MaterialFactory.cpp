#include "MaterialFactory.h"


MaterialFactory::MaterialFactory()
{
}


MaterialFactory::~MaterialFactory()
{
  for (auto materialCreator : m_materialCreators)
  {
    delete materialCreator;
    materialCreator = nullptr;
  }
}

void MaterialFactory::Initialize()
{
  m_materialCreators.push_back(new TextureMaterialCreator());
}

IMaterial* MaterialFactory::GetNewResource(const std::string& filename)
{
  bool result;
  std::string fileInStr;
  std::string type;
  std::string texturePath;
  char input;

  result = FileProcessor::GetFileAsString(filename, fileInStr);
  if (!result) {
    Logger::get().LogMessageWithExceptionDialog(Logger::cantReadFile + filename, __FILE__, __LINE__);
    //TODO FHolod: подставить здесь стандартный материал
  }

  std::stringstream fileStrStream(fileInStr);

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> type;
  
  for (auto materialCreator : m_materialCreators)
  {
    if (materialCreator->CanCreate(type))
      return materialCreator->Get(fileInStr, filename);
  }

  return nullptr;
}