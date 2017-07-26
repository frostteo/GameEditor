#include "ObjMeshConverter.h"

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
    Logger::get().LogMessageWithExceptionDialog(Logger::cantReadFile + sourceFileName, __FILE__, __LINE__);
    return false;
  }

  int vertexCount;
  int textureCoordCount;
  int normalCount;
  int faceCount;

  ReadFileCounts(sourceFileContents, vertexCount, textureCoordCount, normalCount, faceCount);

  result = LoadDataStructures(sourceFileContents, vertexCount, textureCoordCount, normalCount, faceCount);
  if (!result)
  {
    return false;
  }

  CenterToCoordCenter();

  result = SaveModel(destinationFileName);

  if (!result)
  {
    return false;
  }

  return true;
}

void ObjMeshConverter::CenterToCoordCenter()
{
  float minX, minY, minZ, maxX, maxY, maxZ;
  float xCenter, yCenter, zCenter;

  minX = m_txtVertices[0].coord.x;
  maxX = minX;
  minY = m_txtVertices[0].coord.y;
  maxY = minY;
  minZ = m_txtVertices[0].coord.z;
  maxZ = minZ;

  for (auto &txtVertex : m_txtVertices)
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

  xCenter = (maxX - minX) / 2.0f + minX;
  yCenter = (maxY - minY) / 2.0f + minY;
  zCenter = (maxZ - minZ) / 2.0f + minZ;

  for (auto &txtVertex : m_txtVertices)
  {
    txtVertex.coord.x -= xCenter;
    txtVertex.coord.y -= yCenter;
    txtVertex.coord.z -= zCenter;
  }
}

bool ObjMeshConverter::SaveModel(const std::string& destinationFileName)
{
  char space = ' ';
  std::ofstream outputFileStream(destinationFileName.c_str());
  if (outputFileStream.fail())
    return false;

  outputFileStream << "Vertex Count: " << m_txtVertices.size() << std::endl;

  for (auto &txtVertex : m_txtVertices) // access by reference to avoid copying
  {
    outputFileStream << txtVertex.coord.x << space << txtVertex.coord.y << space << txtVertex.coord.z << space <<
      txtVertex.tu << space << txtVertex.tv << space <<
      txtVertex.normal.x << space << txtVertex.normal.y << space << txtVertex.normal.z << space <<
      txtVertex.tangent.x << space << txtVertex.tangent.y << space << txtVertex.tangent.z << space <<
      txtVertex.binormal.x << space << txtVertex.binormal.y << space << txtVertex.binormal.z << std::endl;
  }

  outputFileStream << std::endl;
  outputFileStream << "Index count: " << m_indexes.size() << std::endl;
  for (auto &index : m_indexes)
  {
    outputFileStream << index << std::endl;
  }

  outputFileStream.close();
  FreeMemory();

  return true;
}

void ObjMeshConverter::ReadFileCounts(const std::string& fileInStr, int& vertexCount, int& textureCoordCount, int& normalCount, int& faceCount)
{
  char input;
  std::stringstream fileStrStream(fileInStr);

  vertexCount = 0;
  textureCoordCount = 0;
  normalCount = 0;
  faceCount = 0;

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

    // If the line starts with 'f' then increment the face count.
    if (input == 'f')
    {
      fileStrStream.get(input);
      if (input == ' ') { ++faceCount; }
    }

    // Otherwise read in the remainder of the line.
    while (input != '\n')
    {
      fileStrStream.get(input);
    }

    // Start reading the beginning of the next line.
    fileStrStream.get(input);
  }
}

bool ObjMeshConverter::LoadDataStructures(const std::string& fileInStr, int vertexCount, int textureCount, int normalCount, int faceCount)
{
  std::stringstream sourceFileStrStream(fileInStr);
  std::vector<VertexObj> vertices(vertexCount);
  std::vector<VertexObj> texcoords(textureCount);
  std::vector<VertexObj> normals(normalCount);
  std::vector<FaceObj> faces(faceCount);
  int vertexIndex = 0;
  int texcoordIndex = 0;
  int normalIndex = 0;
  int faceIndex = 0;
  int vIndex, tIndex, nIndex;
  char input, input2;

  m_txtVertices = std::vector<VertexTxt>();
  m_txtVertices.reserve(vertexCount);

  m_indexes = std::vector<int>();
  m_indexes.reserve(vertexCount);

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

    // Read in the faces.
    if (input == 'f')
    {
      sourceFileStrStream.get(input);
      if (input == ' ')
      {
        // Read the face data in backwards to convert it to a left hand system from right hand system.
        for (int i = VERTEX_IN_FACE_OBJ - 1; i >= 0; --i) {
          sourceFileStrStream >> faces[faceIndex].vertexIndexes.index[i] >> input2 >> faces[faceIndex].textCoordIndexes.index[i] >> input2 >> faces[faceIndex].normalIndexes.index[i];
        }

        faceIndex++;
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


  for (int i = 0; i < faceCount; i++)
  {

    vIndex = faces[i].vertexIndexes.index[0] - 1;
    tIndex = faces[i].textCoordIndexes.index[0] - 1;
    nIndex = faces[i].normalIndexes.index[0] - 1;

    VertexTxt vertexTxt;
    vertexTxt.coord.x = vertices[vIndex].x;
    vertexTxt.coord.y = vertices[vIndex].y;
    vertexTxt.coord.z = vertices[vIndex].z;
    vertexTxt.tu = texcoords[tIndex].x;
    vertexTxt.tv = texcoords[tIndex].y;
    vertexTxt.normal.x = normals[nIndex].x;
    vertexTxt.normal.y = normals[nIndex].y;
    vertexTxt.normal.z = normals[nIndex].z;
    //TODO FHolod: calculation of tangent and binormal nust be almost here

    vIndex = faces[i].vertexIndexes.index[1] - 1;
    tIndex = faces[i].textCoordIndexes.index[1] - 1;
    nIndex = faces[i].normalIndexes.index[1] - 1;

    VertexTxt vertexTxt2;
    vertexTxt2.coord.x = vertices[vIndex].x;
    vertexTxt2.coord.y = vertices[vIndex].y;
    vertexTxt2.coord.z = vertices[vIndex].z;
    vertexTxt2.tu = texcoords[tIndex].x;
    vertexTxt2.tv = texcoords[tIndex].y;
    vertexTxt2.normal.x = normals[nIndex].x;
    vertexTxt2.normal.y = normals[nIndex].y;
    vertexTxt2.normal.z = normals[nIndex].z;

    vIndex = faces[i].vertexIndexes.index[2] - 1;
    tIndex = faces[i].textCoordIndexes.index[2] - 1;
    nIndex = faces[i].normalIndexes.index[2] - 1;

    VertexTxt vertexTxt3;
    vertexTxt3.coord.x = vertices[vIndex].x;
    vertexTxt3.coord.y = vertices[vIndex].y;
    vertexTxt3.coord.z = vertices[vIndex].z;
    vertexTxt3.tu = texcoords[tIndex].x;
    vertexTxt3.tv = texcoords[tIndex].y;
    vertexTxt3.normal.x = normals[nIndex].x;
    vertexTxt3.normal.y = normals[nIndex].y;
    vertexTxt3.normal.z = normals[nIndex].z;

    CalculateNormalTangentBinormal(vertexTxt, vertexTxt2, vertexTxt3);

    AddVertex(vertexTxt);
    AddVertex(vertexTxt2);
    AddVertex(vertexTxt3);
  }
  return true;
}

void ObjMeshConverter::AddVertex(const VertexTxt& vertexTxt)
{
  int newIndex = -1;

  const size_t txtVerticesCount = m_txtVertices.size();
  for (size_t k = 0; k < txtVerticesCount; k++)
    if (vertexTxt == m_txtVertices[k]) {
      newIndex = k; // vertext was found, add index
      break;
    }

  if (newIndex == -1) // vertex was not found
  {
    m_txtVertices.push_back(vertexTxt);
    newIndex = m_txtVertices.size() - 1;
  }

  m_indexes.push_back(newIndex);
}

void ObjMeshConverter::CalculateNormalTangentBinormal(VertexTxt& first, VertexTxt& second, VertexTxt& third)
{
  float vector1[3], vector2[3];
  float tuVector[2], tvVector[2];
  float den;
  VertexObj normal, tangent, binormal;

  // Calculate the two vectors for this face.
  vector1[0] = second.coord.x - first.coord.x;
  vector1[1] = second.coord.y - first.coord.y;
  vector1[2] = second.coord.z - first.coord.z;

  vector2[0] = third.coord.x - first.coord.x;
  vector2[1] = third.coord.y - first.coord.y;
  vector2[2] = third.coord.z - first.coord.z;

  // Calculate the tu and tv texture space vectors.
  tuVector[0] = second.tu - first.tu;
  tvVector[0] = third.tv - first.tv;

  tuVector[1] = third.tu - first.tu;
  tvVector[1] = second.tv - first.tv;

  // Calculate the denominator of the tangent/binormal equation.
  den = 1.0f / (tuVector[0] * tvVector[0] - tuVector[1] * tvVector[1]);

  tangent = CalculateTangentOrBinormal(tvVector, vector1, vector2, den);
  binormal = CalculateTangentOrBinormal(tuVector, vector2, vector1, den);

  Normalize(tangent);
  Normalize(binormal);
  normal = CrossProduct(tangent, binormal);
  Normalize(normal);

  first.normal = normal;
  second.normal = normal;
  third.normal = normal;

  first.tangent = tangent;
  second.tangent = tangent;
  third.tangent = tangent;

  first.binormal = binormal;
  second.binormal = binormal;
  third.binormal = binormal;
}

VertexObj ObjMeshConverter::CalculateTangentOrBinormal(float textureVector[2], float modelVectorFirst[3], float modelVectorSecond[3], const float& denominator)
{
  VertexObj result;

  result.x = (textureVector[0] * modelVectorFirst[0] - textureVector[1] * modelVectorSecond[0]) * denominator;
  result.y = (textureVector[0] * modelVectorFirst[1] - textureVector[1] * modelVectorSecond[1]) * denominator;
  result.z = (textureVector[0] * modelVectorFirst[2] - textureVector[1] * modelVectorSecond[2]) * denominator;

  return result;
}

void ObjMeshConverter::Normalize(VertexObj& vertex)
{
  float length;

  // Calculate the length
  length = sqrt((vertex.x * vertex.x) + (vertex.y * vertex.y) + (vertex.z * vertex.z));

  // Normalize vector
  vertex.x = vertex.x / length;
  vertex.y = vertex.y / length;
  vertex.z = vertex.z / length;
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
  m_txtVertices = std::vector<VertexTxt>();
  m_indexes = std::vector<int>();
}