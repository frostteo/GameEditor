#pragma once

#include <fstream>
#include <sstream>
#include "IMeshConverter.h"
#include <vector>
#include <map>
#include "MtlMatLibConverter.h"
#include "VertexTxt.h"

class Logger;
class BoundingBox;

class ObjMeshConverter :
  public IMeshConverter
{
private:
  static const int VERTEX_IN_FACE_OBJ = 3;
  static const std::string m_materialExtension;
  struct FaceObjIndexes
  {
    int index[VERTEX_IN_FACE_OBJ];
  };
  struct FaceObj
  {
    FaceObjIndexes vertexIndexes;
    FaceObjIndexes textCoordIndexes;
    FaceObjIndexes normalIndexes;
  };
 
private:
  std::map<std::string, std::vector<VertexTxt>> m_meshVertexesInfo;
  std::map<std::string, std::vector<int>> m_meshIndexesInfo;
private:
  void Normalize(VertexObj& vertex);
  VertexObj CrossProduct(const VertexObj& first, const VertexObj& second);
  std::shared_ptr<BoundingBox> CenterToCoordCenterAndCaclulateBB();
protected:
  void ReadFileCounts(const std::string& fileInStr, int& vertexCount, int& textureCoordCount, int& normalCount, std::map<std::string, int>& materialFacesCountMap);
  bool LoadDataStructures(const std::string& fileInStr, int vertexCount, int textureCount, int normalCount, std::map<std::string, int>& materialFacesCountMap);
  void CalculateNormalTangentBinormal(VertexTxt& first, VertexTxt& second, VertexTxt& third);
  bool SaveModel(const std::string& destinationFileName, std::shared_ptr<BoundingBox> bb);
  void AddVertex(const VertexTxt& vertexTxt, const std::string& materialName);
  void FreeMemory();
public:
  ObjMeshConverter() { m_fileExtension = "obj"; }
  virtual ~ObjMeshConverter();
  virtual bool ConvertModel(const std::string& sourceFileName, const std::string& destinationFileName) override;
};

