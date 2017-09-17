#pragma once

#include <fstream>
#include <sstream>
#include "IMeshConverter.h"
#include <vector>
#include <map>
#include "Logger.h"

struct VertexObj
{
  float x, y, z;
  bool operator== (const VertexObj& another) const { return this->x == another.x && this->y == another.y && this->z == another.z; }
};

struct VertexTxt
{
  VertexObj coord;
  VertexObj normal;
  VertexObj tangent;
  VertexObj binormal;
  float tv, tu;
  bool operator== (const VertexTxt& other) const {
    return this->coord == other.coord && this->tangent == other.tangent && this->binormal == other.binormal && this->tv == other.tv &&
      this->tu == other.tu;
  }
};

class ObjMeshConverter :
  public IMeshConverter
{
private:
  static const int VERTEX_IN_FACE_OBJ = 3;
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
  std::map<std::string, std::vector<VertexTxt>> m_submeshVertexesInfo;
  std::map<std::string, std::vector<int>> m_submeshIndexesInfo;
private:
  VertexObj CalculateTangentOrBinormal(float textureVector[2], float modelVectorFirst[3], float modelVectorSecond[3], const float& denominator);
  void Normalize(VertexObj& vertex);
  VertexObj CrossProduct(const VertexObj& first, const VertexObj& second);
  void CenterToCoordCenter();
protected:
  void ReadFileCounts(const std::string& fileInStr, int& vertexCount, int& textureCoordCount, int& normalCount, std::map<std::string, int>& materialFacesCountMap);
  bool LoadDataStructures(const std::string& fileInStr, int vertexCount, int textureCount, int normalCount, std::map<std::string, int>& materialFacesCountMap);
  void CalculateNormalTangentBinormal(VertexTxt& first, VertexTxt& second, VertexTxt& third);
  bool SaveModel(const std::string& destinationFileName);
  void AddVertex(const VertexTxt& vertexTxt, const std::string& materialName);
  void FreeMemory();
public:
  ObjMeshConverter()  { m_fileExtension = "obj"; }
  virtual ~ObjMeshConverter();
  virtual bool ConvertModel(const std::string& sourceFileName, const std::string& destinationFileName) override;
};

