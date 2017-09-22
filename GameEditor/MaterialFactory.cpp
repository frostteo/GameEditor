#include "MaterialFactory.h"


MaterialFactory::MaterialFactory()
{
}

void MaterialFactory::Shutdown()
{
  for (auto materialCreator : m_materialCreators)
  {
    delete materialCreator;
    materialCreator = nullptr;
  }
  m_materialCreators.clear();
  SharedResourcesFactory<IMaterial>::Shutdown();
}

MaterialFactory::~MaterialFactory()
{
  Shutdown();
}

MaterialFactory* MaterialFactory::Initialize(TextureFactory* textureFactory, std::string pathToMaterials)
{
  m_pathToMaterials = pathToMaterials;

  Shutdown();
  m_materialCreators.push_back((new TextureMaterialCreator())->SetTextureFactory(textureFactory));
  m_materialCreators.push_back((new SpecularMaterialCreator())->SetTextureFactory(textureFactory));
  m_materialCreators.push_back((new BumpMaterialCreator())->SetTextureFactory(textureFactory));
  m_materialCreators.push_back((new BumpSpecMaterialCreator())->SetTextureFactory(textureFactory));
  m_materialCreators.push_back((new BumpSpecMapMaterialCreator())->SetTextureFactory(textureFactory));

  return this;
}

IMaterial* MaterialFactory::GetNewResource(const std::string& filename)
{
  bool result;
  std::string fileInStr;
  std::string type;
  std::string texturePath;
  char input;

  result = FileProcessor::GetFileAsString(m_pathToMaterials + FileProcessor::FILE_SEPARATOR + filename, fileInStr);
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

  throw std::runtime_error(Logger::get().GetErrorTraceMessage("there is no material creator for: " + type, __FILE__, __LINE__));
}