#include "MtlMatLibConverter.h"

const std::string MtlMatLibConverter::GE_MAT_EXT = ".mat";
const std::string MtlMatLibConverter::MTL_MAT_EXT = ".mtl";

MtlMatLibConverter::~MtlMatLibConverter()
{
}

void MtlMatLibConverter::ConvertMtlMaterials(std::string& sourceFileName, bool needReplaceIfExists)
{
  bool result;
  std::string sourceFileContents;

  if (!CanConvert(sourceFileName))
  {
    Logger::get().ShowCriticalMessage("Can not convert. Invalid file format. Required .mtl");
    return;
  }
   

  result = GetFileAsString(sourceFileName, sourceFileContents);
  if (!result)
  {
    Logger::get().LogMessageWithExceptionDialog(Logger::cantReadFile + sourceFileName, __FILE__, __LINE__);
    return;
  }

  char input;
  const char commentStartChar = '#';

  std::stringstream fileStrStream(sourceFileContents);
  fileStrStream.get(input);
  while (!fileStrStream.eof())
  {
    if (input == 'n')
    {
      std::string continueOfWord;
      fileStrStream >> continueOfWord;
      if (continueOfWord == "ewmtl")
      {
        std::string materialName;
        MtlMaterial mtlMaterial;

        fileStrStream >> materialName;
        readMtlMaterial(fileStrStream, mtlMaterial);

        saveMaterial(materialName, mtlMaterial, needReplaceIfExists);
      }
    }

    // Otherwise read in the remainder of the line.
    while (!fileStrStream.eof() && input != '\n')
    {
      fileStrStream.get(input);
    }

    // Start reading the beginning of the next line.
    fileStrStream.get(input);
  }
}

std::string MtlMatLibConverter::defineMaterialType(const MtlMaterial& material)
{
  //Later here will be cunny algorithm
  return BumpMaterial::bumpMaterialType;
}

void MtlMatLibConverter::saveBumpMaterial(const std::string& materialName, const MtlMaterial& material, bool needReplaceIfExists)
{
  std::string materialFileName = m_pathToMaterials + FileProcessor::FILE_SEPARATOR + materialName + GE_MAT_EXT;
  bool fileExists = FileProcessor::FileExists(materialFileName);

  if (!fileExists || needReplaceIfExists)
  {
    std::ofstream ofstream(materialFileName);
    ofstream << "type: " << BumpMaterial::bumpMaterialType << std::endl;
    ofstream << "textureFileName: " << material.map_Kd << std::endl;
    ofstream << "normalMap: " << material.map_bump << std::endl;
    ofstream << "bumpDepth: " << material.bumpPower << std::endl;
  }
}

void MtlMatLibConverter::readMtlMaterial(std::stringstream& strStream, MtlMaterial& material)
{
  std::string space;

  strStream >> space >> material.Ns;
  strStream >> space >> material.Ni;
  strStream >> space >> material.d;
  strStream >> space >> material.Tr;
  strStream >> space >> material.Tf.r >> material.Tf.g >> material.Tf.b;
  strStream >> space >> material.illum;
  strStream >> space >> material.Ka.r >> material.Ka.g >> material.Ka.b;
  strStream >> space >> material.Kd.r >> material.Kd.g >> material.Kd.b;
  strStream >> space >> material.Ks.r >> material.Ks.g >> material.Ks.b;
  strStream >> space >> material.Ke.r >> material.Ke.g >> material.Ke.b;

  strStream >> space;
  std::getline(strStream, material.map_Ka);
  material.map_Ka = Utils::Trim(material.map_Ka);

  strStream >> space;
  std::getline(strStream, material.map_Kd);
  material.map_Kd = Utils::Trim(material.map_Kd);

  strStream >> space >> space >> material.bumpPower;
  std::getline(strStream, material.map_bump);
  material.map_bump = Utils::Trim(material.map_bump);
}

void MtlMatLibConverter::saveMaterial(const std::string& materialName, const MtlMaterial& material, bool needReplaceIfExists)
{
  std::string materialType = defineMaterialType(material);

  if (materialType == BumpMaterial::bumpMaterialType)
  {
    saveBumpMaterial(materialName, material, needReplaceIfExists);
  }
}