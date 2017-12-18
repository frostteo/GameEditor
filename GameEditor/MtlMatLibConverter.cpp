#include "MtlMatLibConverter.h"

const std::string MtlMatLibConverter::GE_MAT_EXT = ".mat";
const std::string MtlMatLibConverter::MTL_MAT_EXT = ".mtl";
const std::string MtlMatLibConverter::NEW_MAT_DESCRIPTOR = "newmtl";

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

  std::stringstream fileStrStream(sourceFileContents);
  fileStrStream >> m_space;
  while (!fileStrStream.eof())
  {
    if (m_space == MtlMatLibConverter::NEW_MAT_DESCRIPTOR)
    {
        std::string materialName;
        MtlMaterial mtlMaterial;

        fileStrStream >> materialName;
        readMtlMaterial(fileStrStream, mtlMaterial);
        saveMaterial(materialName, mtlMaterial, needReplaceIfExists);
    }
    else { 
      fileStrStream >> m_space;
    }
  }
}

std::string MtlMatLibConverter::defineMaterialType(const MtlMaterial& material)
{
  //TODO FHolod: algorithm will be extended
  if (!material.map_Kd.empty() && !material.map_bump.empty())
    return BumpMaterial::bumpMaterialType;
  else if (!material.map_Kd.empty() && HasSpecularData(material))
    return SpecularMaterial::specularMaterialType;
  else if (!material.map_Kd.empty())
    return TextureMaterial::textureMaterialType;
  else return ColorMaterial::colorMaterialType;
}

void MtlMatLibConverter::saveBumpMaterial(std::ofstream& ofstream, const MtlMaterial& material)
{
    ofstream << "type: " << BumpMaterial::bumpMaterialType << std::endl;
    ofstream << "textureFileName: " << material.map_Kd << std::endl;
    ofstream << "normalMap: " << material.map_bump << std::endl;
    ofstream << "bumpDepth: " << material.bumpPower << std::endl;
}

void MtlMatLibConverter::saveSpecularMaterialType(std::ofstream& ofstream, const MtlMaterial& material)
{
  ofstream << "type: " << SpecularMaterial::specularMaterialType << std::endl;
  ofstream << "textureFileName: " << material.map_Kd << std::endl;
  ofstream << "specularColor: " << material.Ks.r << ' ' << material.Ks.g << ' ' << material.Ks.b << ' ' << 1.0f << std::endl;
  ofstream << "specularPower: " << material.Ns << std::endl;
}

void MtlMatLibConverter::saveColorMaterial(std::ofstream& ofstream, const MtlMaterial& material)
{
  ColorMaterialSubType subType = static_cast<ColorMaterialSubType>(0);

  if (material.Ke.r > 0 && material.Ke.g > 0 && material.Ke.b > 0)
    subType |= ColorMaterialSubType::COLOR_SELFILUM;

  if (HasSpecularData(material))
    subType |= ColorMaterialSubType::COLOR_SPECULAR;

  if (material.d < 1)
    subType |= ColorMaterialSubType::COLOR_TRANSPARENT;

  ofstream << "type: " << ColorMaterial::colorMaterialType << std::endl;
  ofstream << "diffuseColor: " << material.Kd.r << ' ' << material.Kd.g << ' ' << material.Kd.b << ' ' << 1.0f << std::endl;
  ofstream << "specularColor: " << material.Ks.r << ' ' << material.Ks.g << ' ' << material.Ks.b << ' ' << 1.0f << std::endl;
  ofstream << "selfIluminationColor: " << material.Ke.r << ' ' << material.Ke.g << ' ' << material.Ke.b << ' ' << 1.0f << std::endl;
  ofstream << "specularPower: " << material.Ns << std::endl;
  ofstream << "opacity: " << material.d << std::endl;
  ofstream << "subType: " << static_cast<int>(subType) << std::endl;
}

void MtlMatLibConverter::readMtlMaterial(std::stringstream& strStream, MtlMaterial& material)
{
  strStream >> m_space >> material.Ns;
  strStream >> m_space >> material.Ni;
  strStream >> m_space >> material.d;
  strStream >> m_space >> material.Tr;
  strStream >> m_space >> material.Tf.r >> material.Tf.g >> material.Tf.b;
  strStream >> m_space >> material.illum;
  strStream >> m_space >> material.Ka.r >> material.Ka.g >> material.Ka.b;
  strStream >> m_space >> material.Kd.r >> material.Kd.g >> material.Kd.b;
  strStream >> m_space >> material.Ks.r >> material.Ks.g >> material.Ks.b;
  strStream >> m_space >> material.Ke.r >> material.Ke.g >> material.Ke.b;

  strStream >> m_space;
  while (!strStream.eof() && m_space != MtlMatLibConverter::NEW_MAT_DESCRIPTOR)
  {
    if (m_space == "map_Ka") {
      std::getline(strStream, material.map_Ka);
      material.map_Ka = Utils::Trim(material.map_Ka);
      std::replace(material.map_Ka.begin(), material.map_Ka.end(), MtlMatLibConverter::MTL_FILE_SEPARATOR, FileProcessor::FILE_SEPARATOR);
    }
    else if (m_space == "map_Kd") {
      std::getline(strStream, material.map_Kd);
      material.map_Kd = Utils::Trim(material.map_Kd);
      std::replace(material.map_Kd.begin(), material.map_Kd.end(), MtlMatLibConverter::MTL_FILE_SEPARATOR, FileProcessor::FILE_SEPARATOR);
    }
    else if (m_space == "map_bump") {
      strStream >> m_space >> material.bumpPower;
      std::getline(strStream, material.map_bump);
      material.map_bump = Utils::Trim(material.map_bump);
      std::replace(material.map_bump.begin(), material.map_bump.end(), MtlMatLibConverter::MTL_FILE_SEPARATOR, FileProcessor::FILE_SEPARATOR);
    }
    strStream >> m_space;
  }
}

void MtlMatLibConverter::saveMaterial(const std::string& materialName, const MtlMaterial& material, bool needReplaceIfExists)
{
  std::string materialFileName = m_pathToMaterials + FileProcessor::FILE_SEPARATOR + materialName + GE_MAT_EXT;
  bool fileExists = FileProcessor::FileExists(materialFileName);

  if (!fileExists || needReplaceIfExists)
  {
    std::string materialType = defineMaterialType(material);
    std::ofstream ofstream(materialFileName);

    if (materialType == BumpMaterial::bumpMaterialType)
      saveBumpMaterial(ofstream, material);
    else if (materialType == SpecularMaterial::specularMaterialType)
      saveSpecularMaterialType(ofstream, material);
    else if (materialType == TextureMaterial::textureMaterialType)
      saveTextureMaterial(ofstream, material);
    else if (materialType == ColorMaterial::colorMaterialType)
      saveColorMaterial(ofstream, material);
  }
}

void MtlMatLibConverter::saveTextureMaterial(std::ofstream& ofstream, const MtlMaterial& material)
{
  ofstream << "type: " << TextureMaterial::textureMaterialType << std::endl;
  ofstream << "textureFileName: " << material.map_Kd << std::endl;
}