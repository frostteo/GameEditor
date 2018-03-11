#include "Model.h"
#include "BoundingBox.h"
#include "Logger.h"
#include "MaterialFactory.h"
#include "FileProcessor.h"
#include "VertexTxt.h"
#include "Mesh.h"

Model::Model(
  std::string fileName,
  ID3D11Device* device,
  MaterialFactory& materialFactory
  )
  : m_fileName(fileName),
    m_meshes(),
    m_boundingBox(new BoundingBox)
{
  LoadModel(device, materialFactory);
}

void Model::LoadModel(
  ID3D11Device* device,
  MaterialFactory& materialFactory
  )
{
  std::string fileInStr;
  bool result = FileProcessor::GetFileAsString(m_fileName, fileInStr);

  if (!result)
    RUNTIME_ERROR("Can't read file " + m_fileName);

  std::stringstream fileStrStream(fileInStr);
  m_boundingBox->Deserialize(fileStrStream);
  while (!fileStrStream.eof())
    LoadMesh(fileStrStream, device, materialFactory);
}

void Model::LoadMesh(
  std::stringstream& stream,
  ID3D11Device* device,
  MaterialFactory& materialFactory
  )
{
  char input;
  std::string materialName;
  int vertexCount;
  int indexCount;
  std::vector<MeshVertex> vertexes;
  std::vector<unsigned long> indexes;
  VertexTxt vertexTxt;
  MeshVertex vertexInBuffer;
  unsigned long index;
  std::unique_ptr<Mesh> mesh;

  stream.get(input);
  while (input != ':')
  {
    if (stream.eof())
      return;
    stream.get(input);
  }

  stream >> materialName;

  stream.get(input);
  while (input != ':')
  {
    if (stream.eof())
      return;
    stream.get(input);
  }
  stream >> vertexCount;
  vertexes.reserve(vertexCount);

  for (int i = 0; i < vertexCount; ++i)
  {
    stream >> vertexTxt.coord.x >> vertexTxt.coord.y >> vertexTxt.coord.z;
    stream >> vertexTxt.tu >> vertexTxt.tv;
    stream >> vertexTxt.normal.x >> vertexTxt.normal.y >> vertexTxt.normal.z;
    stream >> vertexTxt.tangent.x >> vertexTxt.tangent.y >> vertexTxt.tangent.z;
    stream >> vertexTxt.binormal.x >> vertexTxt.binormal.y >> vertexTxt.binormal.z;

    vertexInBuffer.position = XMFLOAT3(vertexTxt.coord.x, vertexTxt.coord.y, vertexTxt.coord.z);
    vertexInBuffer.texture = XMFLOAT2(vertexTxt.tu, vertexTxt.tv);
    vertexInBuffer.normal = XMFLOAT3(vertexTxt.normal.x, vertexTxt.normal.y, vertexTxt.normal.z);
    vertexInBuffer.tangent = XMFLOAT3(vertexTxt.tangent.x, vertexTxt.tangent.y, vertexTxt.tangent.z);
    vertexInBuffer.binormal = XMFLOAT3(vertexTxt.binormal.x, vertexTxt.binormal.y, vertexTxt.binormal.z);

    vertexes.push_back(vertexInBuffer);
  }

  stream.get(input);
  while (input != ':')
  {
    if (stream.eof())
      return;
    stream.get(input);
  }

  stream >> indexCount;
  indexes.reserve(indexCount);

  for (int i = 0; i < indexCount; ++i)
  {
    stream >> index;
    indexes.push_back(index);
  }

  mesh = std::unique_ptr<Mesh>(new Mesh(device, m_fileName, vertexes, indexes, materialFactory.GetResource(materialName)));
  m_meshes.push_back(std::move(mesh));
}

Model::~Model()
{

}