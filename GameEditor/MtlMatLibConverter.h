#pragma once

#include <algorithm>
#include "IConverter.h"
#include "Logger.h"
#include "BumpMaterial.h"
#include "Utils.h"

class MtlMatLibConverter : public IConverter
{
public:

  struct MtlColor {
    float r;
    float g;
    float b;
  };

  struct MtlMaterial {
    float Ns;
    float Ni;
    float d;
    float Tr;
    MtlColor Tf;
    int illum;
    MtlColor Ka;
    MtlColor Kd;
    MtlColor Ks;
    MtlColor Ke;
    std::string map_Ka;
    std::string map_Kd;
    float bumpPower;
    std::string map_bump;
  };
protected:
  static const char MTL_FILE_SEPARATOR = '\\';
  std::string m_pathToMaterials;
protected:
  void readMtlMaterial(std::stringstream& strStream, MtlMaterial& material);
  void saveMaterial(const std::string& materialName, const MtlMaterial& material, bool needReplaceIfExists);
  std::string defineMaterialType(const MtlMaterial& material);
  void saveBumpMaterial(const std::string& materialName, const MtlMaterial& material, bool needReplaceIfExists);
public:
  static const std::string GE_MAT_EXT;
  static const std::string MTL_MAT_EXT;
public:
  MtlMatLibConverter(std::string pathToMaterials) { m_fileExtension = MTL_MAT_EXT.substr(1); m_pathToMaterials = pathToMaterials; }
  virtual ~MtlMatLibConverter();
  void ConvertMtlMaterials(std::string& sourceFileName, bool needReplaceIfExists = false);
 
};

