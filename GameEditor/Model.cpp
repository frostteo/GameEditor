#include "Model.h"


Model::Model(
  std::string fileName,
  ID3D11Device* device,
  MaterialFactory* materialFactory,
  ShaderFactory* shaderFactory
  )
{
  m_fileName = fileName;
  LoadData(device, materialFactory, shaderFactory);
}

void Model::LoadData(
  ID3D11Device* device,
  MaterialFactory* materialFactory,
  ShaderFactory* shaderFactory
  )
{
  std::string fileInStr;
  bool result = FileProcessor::GetFileAsString(m_fileName, fileInStr);

  if (!result)
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("Can't read file " + m_fileName, __FILE__, __LINE__));

  std::stringstream fileStrStream(fileInStr);
  while (!fileStrStream.eof())
    LoadSubMesh(fileStrStream, device, materialFactory, shaderFactory);
}

void Model::LoadSubMesh(
  std::stringstream& stream,
  ID3D11Device* device,
  MaterialFactory* materialFactory,
  ShaderFactory* shaderFactory
  )
{
  char input;
  std::string materialName;
  int vertexCount;
  int indexCount;
  std::vector<SubMesh::VertexInBuffer> vertexes;
  std::vector<unsigned long> indexes;
  VertexTxt vertexTxt;
  SubMesh::VertexInBuffer vertexInBuffer;
  unsigned long index;

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

  SubMesh* submesh = new SubMesh(device, m_fileName, materialName, vertexes, indexes, materialFactory, shaderFactory);
  m_submeshes.push_back(submesh);
}

void Model::Render(ID3D11DeviceContext* deviceContext, XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix, LightininigSystem* lightining, XMFLOAT3& cameraPostion)
{
  XMMATRIX worldMatrix;
  this->GetWorldMatrix(worldMatrix);

  for (auto submesh : m_submeshes)
    submesh->Render(deviceContext, worldMatrix, viewMatrix, projectionMatrix, lightining, cameraPostion);
}

Model::~Model()
{
  for (auto submesh : m_submeshes)
  {
    delete submesh;
    submesh = nullptr;
  }
}
