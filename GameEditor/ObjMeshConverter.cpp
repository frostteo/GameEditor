#include "ObjMeshConverter.h"
#include "Logger.h"
#include "BoundingBox.h"

const std::string ObjMeshConverter::m_materialExtension = MtlMatLibConverter::GE_MAT_EXT;

ObjMeshConverter::~ObjMeshConverter()
{
}

bool ObjMeshConverter::ConvertModel(const std::string& sourceFileName, const std::string& destinationFileName)
{
  bool result;
  std::string sourceFileContents;

  if (!CanConvert(sourceFileName))
    return false;

  result = GetFileAsString(sourceFileName, sourceFileContents);
  if (!result)
  {
    CANT_READ_FILE_ERROR(sourceFileName);
    return false;
  }

  int vertexCount;
  int textureCoordCount;
  int normalCount;

  std::map<std::string, int> materialFacesCountMap;
  ReadFileCounts(sourceFileContents, vertexCount, textureCoordCount, normalCount, materialFacesCountMap);

  result = LoadDataStructures(sourceFileContents, vertexCount, textureCoordCount, normalCount, materialFacesCountMap);
  if (!result)
  {
    return false;
  }

  auto boundingBox = CenterToCoordCenterAndCaclulateBB();

  result = SaveModel(destinationFileName, boundingBox);

  if (!result)
  {
    return false;
  }

  return true;
}

std::shared_ptr<BoundingBox> ObjMeshConverter::CenterToCoordCenterAndCaclulateBB()
{
  float minX, minY, minZ, maxX, maxY, maxZ;
  float xCenter, yCenter, zCenter;

  minX = m_meshVertexesInfo.begin()->second[0].coord.x;
  maxX = minX;
  minY = m_meshVertexesInfo.begin()->second[0].coord.y;
  maxY = minY;
  minZ = m_meshVertexesInfo.begin()->second[0].coord.z;
  maxZ = minZ;

  for (auto &meshVertexInfo : m_meshVertexesInfo)
  {
    for (auto &txtVertex : meshVertexInfo.second)
    {
      if (txtVertex.coord.x < minX)
        minX = txtVertex.coord.x;

      if (txtVertex.coord.y < minY)
        minY = txtVertex.coord.y;

      if (txtVertex.coord.z < minZ)
        minZ = txtVertex.coord.z;


      if (txtVertex.coord.x > maxX)
        maxX = txtVertex.coord.x;

      if (txtVertex.coord.y > maxY)
        maxY = txtVertex.coord.y;

      if (txtVertex.coord.z > maxZ)
        maxZ = txtVertex.coord.z;
    }
  }
 
  xCenter = (maxX - minX) / 2.0f + minX;
  yCenter = (maxY - minY) / 2.0f + minY;
  zCenter = (maxZ - minZ) / 2.0f + minZ;

  for (auto &meshVertexInfo : m_meshVertexesInfo)
  {
    for (auto &txtVertex : meshVertexInfo.second)
    {
      txtVertex.coord.x -= xCenter;
      txtVertex.coord.y -= yCenter;
      txtVertex.coord.z -= zCenter;
    }
  }

  minX -= xCenter;
  minY -= yCenter;
  minZ -= zCenter;
  maxX -= xCenter;
  maxY -= yCenter;
  maxZ -= zCenter;

  auto boundingBox = std::make_shared<BoundingBox>();
  boundingBox->Initialize(minX, minY, minZ, maxX, maxY, maxZ);
  return boundingBox;
}

bool ObjMeshConverter::SaveModel(const std::string& destinationFileName, std::shared_ptr<BoundingBox> bb)
{
  char space = ' ';
  std::ofstream outputFileStream(destinationFileName.c_str());
  if (outputFileStream.fail())
    return false;

  bb->Serialize(outputFileStream);

  for (const auto& meshInfo : m_meshVertexesInfo)
  {
    outputFileStream << "Material name: " << meshInfo.first + ObjMeshConverter::m_materialExtension << std::endl;
    outputFileStream << "Vertex Count: " << meshInfo.second.size() << std::endl;
    for (const auto& txtVertex : meshInfo.second)
    {
      outputFileStream << txtVertex.coord.x << space << txtVertex.coord.y << space << txtVertex.coord.z << space <<
        txtVertex.tu << space << txtVertex.tv << space <<
        txtVertex.normal.x << space << txtVertex.normal.y << space << txtVertex.normal.z << space <<
        txtVertex.tangent.x << space << txtVertex.tangent.y << space << txtVertex.tangent.z << space <<
        txtVertex.binormal.x << space << txtVertex.binormal.y << space << txtVertex.binormal.z << std::endl;
    }

    outputFileStream << "Index count: " << m_meshIndexesInfo[meshInfo.first].size() << std::endl;

    for (auto &index : m_meshIndexesInfo[meshInfo.first])
    {
      outputFileStream << index << std::endl;
    }
  }

  outputFileStream.close();
  FreeMemory();

  return true;
}

void ObjMeshConverter::ReadFileCounts(const std::string& fileInStr, int& vertexCount, int& textureCoordCount, int& normalCount, std::map<std::string, int>& materialFacesCountMap)
{
  char input;
  std::stringstream fileStrStream(fileInStr);

  vertexCount = 0;
  textureCoordCount = 0;
  normalCount = 0;
  materialFacesCountMap.clear();
  std::string lastUsedMaterialName;

  // Read from the file and continue to read until the end of the file is reached.
  fileStrStream.get(input);
  while (!fileStrStream.eof())
  {
    // If the line starts with 'v' then count either the vertex, the texture coordinates, or the normal vector.
    if (input == 'v')
    {
      fileStrStream.get(input);
      if (input == ' ') { ++vertexCount; }
      if (input == 't') { ++textureCoordCount; }
      if (input == 'n') { ++normalCount; }
    }

    if (input == 'u')
    {
      std::string continueOfWord;
      fileStrStream >> continueOfWord;
      if (continueOfWord == "semtl") //mesh description
      {
        std::string materialName;
        fileStrStream >> materialName;
        lastUsedMaterialName = materialName;
      }
    }

    if (input == 'f')
      ++materialFacesCountMap[lastUsedMaterialName];

    // Otherwise read in the remainder of the line.
    while (input != '\n')
    {
      fileStrStream.get(input);
    }

    // Start reading the beginning of the next line.
    fileStrStream.get(input);
  }
}

bool ObjMeshConverter::LoadDataStructures(const std::string& fileInStr, int vertexCount, int textureCount, int normalCount, std::map<std::string, int>& materialFacesCountMap)
{
  std::stringstream sourceFileStrStream(fileInStr);
  std::vector<VertexObj> vertices(vertexCount);
  std::vector<VertexObj> texcoords(textureCount);
  std::vector<VertexObj> normals(normalCount);
  std::map<std::string, std::vector<FaceObj>> meshesInfo;
  std::string lastUsedMaterialName;

  FreeMemory();
  for (const auto &materialFaceCount : materialFacesCountMap) {
    meshesInfo[materialFaceCount.first] = std::vector<FaceObj>();
    meshesInfo[materialFaceCount.first].reserve(materialFaceCount.second);

    m_meshVertexesInfo[materialFaceCount.first] = std::vector<VertexTxt>();
    m_meshVertexesInfo[materialFaceCount.first].reserve(materialFaceCount.second * VERTEX_IN_FACE_OBJ);

    m_meshIndexesInfo[materialFaceCount.first] = std::vector<int>();
    m_meshIndexesInfo[materialFaceCount.first].reserve(materialFaceCount.second * VERTEX_IN_FACE_OBJ);
  }

  int vertexIndex = 0;
  int texcoordIndex = 0;
  int normalIndex = 0;
  int vIndex, tIndex, nIndex;
  char input;
  const char slash = '/';
  const int emptyIndex = 0;

  sourceFileStrStream.get(input);
  while (!sourceFileStrStream.eof())
  {
    if (input == 'v')
    {
      sourceFileStrStream.get(input);

      // Read in the vertices.
      if (input == ' ')
      {
        sourceFileStrStream >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

        // Invert the Z vertex to change to left hand system.
        vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
        vertexIndex++;
      }

      // Read in the texture uv coordinates.
      if (input == 't')
      {
        sourceFileStrStream >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

        // Invert the V texture coordinates to left hand system.
        texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
        texcoordIndex++;
      }

      // Read in the normals.
      if (input == 'n')
      {
        sourceFileStrStream >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

        // Invert the Z normal to change to left hand system.
        normals[normalIndex].z = normals[normalIndex].z * -1.0f;
        normalIndex++;
      }
    }

    if (input == 'u')
    {
      std::string continueOfWord;
      sourceFileStrStream >> continueOfWord;
      if (continueOfWord == "semtl") //mesh description
      {
        std::string materialName;
        sourceFileStrStream >> materialName;
        lastUsedMaterialName = materialName;
      }
    }

    // Read in the faces.
    if (input == 'f')
    {
      sourceFileStrStream.get(input);
      if (input == ' ')
      {
        FaceObj face;
        // Read the face data in backwards to convert it to a left hand system from right hand system.
        for (int i = VERTEX_IN_FACE_OBJ - 1; i >= 0; --i) {
          sourceFileStrStream >> face.vertexIndexes.index[i];
          sourceFileStrStream.ignore();

          if (sourceFileStrStream.peek() == slash)
            face.textCoordIndexes.index[i] = emptyIndex;
          else
            sourceFileStrStream >> face.textCoordIndexes.index[i];

          sourceFileStrStream.ignore();
          sourceFileStrStream >> face.normalIndexes.index[i];
        }
        meshesInfo[lastUsedMaterialName].push_back(face);
      }
    }

    // Read in the remainder of the line.
    while (input != '\n')
    {
      sourceFileStrStream.get(input);
    }

    // Start reading the beginning of the next line.
    sourceFileStrStream.get(input);
  }

  for (const auto &mesheInfo : meshesInfo)
  {
    for (int i = 0; i < mesheInfo.second.size(); ++i)
    {
      vIndex = mesheInfo.second[i].vertexIndexes.index[0] - 1;
      tIndex = mesheInfo.second[i].textCoordIndexes.index[0] - 1;
      nIndex = mesheInfo.second[i].normalIndexes.index[0] - 1;

      VertexTxt vertexTxt;
      bool faceHasTextureCoords = true;
      vertexTxt.coord.x = vertices[vIndex].x;
      vertexTxt.coord.y = vertices[vIndex].y;
      vertexTxt.coord.z = vertices[vIndex].z;

      if (tIndex >= 0) {
        vertexTxt.tu = texcoords[tIndex].x;
        vertexTxt.tv = texcoords[tIndex].y;
      }
      else {
        faceHasTextureCoords = false;
      }

      vertexTxt.normal.x = normals[nIndex].x;
      vertexTxt.normal.y = normals[nIndex].y;
      vertexTxt.normal.z = normals[nIndex].z;

      vIndex = mesheInfo.second[i].vertexIndexes.index[1] - 1;
      tIndex = mesheInfo.second[i].textCoordIndexes.index[1] - 1;
      nIndex = mesheInfo.second[i].normalIndexes.index[1] - 1;

      VertexTxt vertexTxt2;
      vertexTxt2.coord.x = vertices[vIndex].x;
      vertexTxt2.coord.y = vertices[vIndex].y;
      vertexTxt2.coord.z = vertices[vIndex].z;

      if (tIndex >= 0) {
        vertexTxt2.tu = texcoords[tIndex].x;
        vertexTxt2.tv = texcoords[tIndex].y;
      }
      else {
        faceHasTextureCoords = false;
      }

      vertexTxt2.normal.x = normals[nIndex].x;
      vertexTxt2.normal.y = normals[nIndex].y;
      vertexTxt2.normal.z = normals[nIndex].z;

      vIndex = mesheInfo.second[i].vertexIndexes.index[2] - 1;
      tIndex = mesheInfo.second[i].textCoordIndexes.index[2] - 1;
      nIndex = mesheInfo.second[i].normalIndexes.index[2] - 1;

      VertexTxt vertexTxt3;
      vertexTxt3.coord.x = vertices[vIndex].x;
      vertexTxt3.coord.y = vertices[vIndex].y;
      vertexTxt3.coord.z = vertices[vIndex].z;

      if (tIndex >= 0) {
        vertexTxt3.tu = texcoords[tIndex].x;
        vertexTxt3.tv = texcoords[tIndex].y;
      }
      else {
        faceHasTextureCoords = false;
      }

      vertexTxt3.normal.x = normals[nIndex].x;
      vertexTxt3.normal.y = normals[nIndex].y;
      vertexTxt3.normal.z = normals[nIndex].z;

      if (faceHasTextureCoords)
        CalculateNormalTangentBinormal(vertexTxt, vertexTxt2, vertexTxt3);

      AddVertex(vertexTxt, mesheInfo.first);
      AddVertex(vertexTxt2, mesheInfo.first);
      AddVertex(vertexTxt3, mesheInfo.first);
    }
  }

  return true;
}

void ObjMeshConverter::AddVertex(const VertexTxt& vertexTxt, const std::string& materialName)
{
  int newIndex = -1;

  const size_t txtVerticesCount = m_meshVertexesInfo[materialName].size();
  for (size_t k = 0; k < txtVerticesCount; k++)
    if (vertexTxt == m_meshVertexesInfo[materialName][k]) {
      newIndex = k; // vertext was found, add index
      break;
    }

  if (newIndex == -1) // vertex was not found
  {
    m_meshVertexesInfo[materialName].push_back(vertexTxt);
    newIndex = m_meshVertexesInfo[materialName].size() - 1;
  }

  m_meshIndexesInfo[materialName].push_back(newIndex);
}

void ObjMeshConverter::CalculateNormalTangentBinormal(VertexTxt& first, VertexTxt& second, VertexTxt& third)
{
  //TODO FHolod: I can rewrite this method because the algorithm is not exact
  float vector1[3], vector2[3];
  float tuVector[2], tvVector[2];
  float den;
  VertexObj tangent, binormal;

  // Calculate the two vectors for this face.
  vector1[0] = second.coord.x - first.coord.x;
  vector1[1] = second.coord.y - first.coord.y;
  vector1[2] = second.coord.z - first.coord.z;

  vector2[0] = third.coord.x - first.coord.x;
  vector2[1] = third.coord.y - first.coord.y;
  vector2[2] = third.coord.z - first.coord.z;

  // Calculate the tu and tv texture space vectors.
  tuVector[0] = second.tu - first.tu;
  tvVector[0] = second.tv - first.tv;

  tuVector[1] = third.tu - first.tu;
  tvVector[1] = third.tv - first.tv;


  // Calculate the denominator of the tangent/binormal equation.
  float textCoordDiff = tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0];
  if (textCoordDiff == 0)
    den = 1.0f;
  else
    den = 1.0f / textCoordDiff;

  tangent.x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
  tangent.y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
  tangent.z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;

  binormal.x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * den;
  binormal.y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * den;
  binormal.z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * den;

  Normalize(tangent);
  Normalize(binormal);

  first.tangent = tangent;
  second.tangent = tangent;
  third.tangent = tangent;

  first.binormal = binormal;
  second.binormal = binormal;
  third.binormal = binormal;
}

void ObjMeshConverter::Normalize(VertexObj& vertex)
{
  float length;

  // Calculate the length
  length = sqrt((vertex.x * vertex.x) + (vertex.y * vertex.y) + (vertex.z * vertex.z));

  if (length != 0) {
    // Normalize vector
    vertex.x = vertex.x / length;
    vertex.y = vertex.y / length;
    vertex.z = vertex.z / length;
  }
}

VertexObj ObjMeshConverter::CrossProduct(const VertexObj& first, const VertexObj& second)
{
  VertexObj result;

  result.x = first.y * second.z - first.z * second.y;
  result.y = first.z * second.x - first.x * second.z;
  result.z = first.x * second.y - first.y * second.x;

  return result;
}

void ObjMeshConverter::FreeMemory()
{
  m_meshVertexesInfo = std::map<std::string, std::vector<VertexTxt>>();
  m_meshIndexesInfo = std::map<std::string, std::vector<int>>();
}