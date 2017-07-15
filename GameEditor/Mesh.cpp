#include "Mesh.h"


Mesh::Mesh()
{
  m_vertexBuffer = nullptr;
  m_indexBuffer = nullptr;
}

Mesh::~Mesh()
{
  Shutdown();
}

bool Mesh::Initialize(ID3D11Device* device, const std::string& meshFileName)
{
  bool result;

  m_fileName = meshFileName;
  
  result = LoadMesh();
  if (!result)
  {
    Logger::get().LogMessageWithExceptionDialog(Logger::cantReadFile + meshFileName, __FILE__, __LINE__);
    return false;
  }
  
  result = InitializeBuffers(device);
  if (!result)
  {
    Logger::get().LogMessage("cant initializebuffers", __FILE__, __LINE__);
    return false;
  }

  return true;
}

bool Mesh::LoadMesh()
{
  bool result;
  char input;
  int vertexCount;
  int indexCount;
  VertexTxt vertex;
  VertexInBuffer vertexInBuffer;
  unsigned long index;
  std::string fileInStr;
  result = FileProcessor::GetFileAsString(m_fileName, fileInStr);

  if (!result)
  {
    return false;
  }

  std::stringstream fileStrStream(fileInStr);

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }

  fileStrStream >> vertexCount;
  m_vertices = std::vector<VertexInBuffer>();
  m_vertices.reserve(vertexCount);

  for (int i = 0; i < vertexCount; ++i)
  {
    fileStrStream >> vertex.coord.x >> vertex.coord.y >> vertex.coord.z;
    fileStrStream >> vertex.tu >> vertex.tv;
    fileStrStream >> vertex.normal.x >> vertex.normal.y >> vertex.normal.z;
    fileStrStream >> vertex.tangent.x >> vertex.tangent.y >> vertex.tangent.z;
    fileStrStream >> vertex.binormal.x >> vertex.binormal.y >> vertex.binormal.z;

    vertexInBuffer.position = XMFLOAT3(vertex.coord.x, vertex.coord.y, vertex.coord.z);
    vertexInBuffer.texture = XMFLOAT2(vertex.tu, vertex.tv);
    vertexInBuffer.normal = XMFLOAT3(vertex.normal.x, vertex.normal.y, vertex.normal.z);
    vertexInBuffer.tangent = XMFLOAT3(vertex.tangent.x, vertex.tangent.y, vertex.tangent.z);
    vertexInBuffer.binormal = XMFLOAT3(vertex.binormal.x, vertex.binormal.y, vertex.binormal.z);

    m_vertices.push_back(vertexInBuffer);
  }

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }

  fileStrStream >> indexCount;

  m_indexes = std::vector<unsigned long>();
  m_indexes.reserve(indexCount);

  for (int i = 0; i < indexCount; ++i)
  {
    fileStrStream >> index;
    m_indexes.push_back(index);
  }

  return true;
}

bool Mesh::InitializeBuffers(ID3D11Device* device)
{
  D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
  D3D11_SUBRESOURCE_DATA vertexData, indexData;
  HRESULT result;

  // Set up the description of the static vertex buffer.
  vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  vertexBufferDesc.ByteWidth = sizeof(VertexInBuffer) * m_vertices.size();
  vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  vertexBufferDesc.CPUAccessFlags = 0;
  vertexBufferDesc.MiscFlags = 0;
  vertexBufferDesc.StructureByteStride = 0;

  // Give the subresource structure a pointer to the vertex data.
  vertexData.pSysMem = &m_vertices[0];
  vertexData.SysMemPitch = 0;
  vertexData.SysMemSlicePitch = 0;

  // Now create the vertex buffer.
  result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
  if (FAILED(result))
  {
    return false;
  }

  // Set up the description of the static index buffer.
  indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexes.size();
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.CPUAccessFlags = 0;
  indexBufferDesc.MiscFlags = 0;
  indexBufferDesc.StructureByteStride = 0;

  // Give the subresource structure a pointer to the index data.
  indexData.pSysMem = &m_indexes[0];
  indexData.SysMemPitch = 0;
  indexData.SysMemSlicePitch = 0;

  // Create the index buffer.
  result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
  if (FAILED(result))
  {
    return false;
  }

  return true;
}

void Mesh::Render(ID3D11DeviceContext* deviceContext)
{
  unsigned int stride;
  unsigned int offset;


  // Set vertex buffer stride and offset.
  stride = sizeof(VertexInBuffer);
  offset = 0;

  // Set the vertex buffer to active in the input assembler so it can be rendered.
  deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

  // Set the index buffer to active in the input assembler so it can be rendered.
  deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

  // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  return;
}

void Mesh::Shutdown()
{
  // Shutdown the vertex and index buffers.
  ShutdownBuffers();
}

void Mesh::ShutdownBuffers()
{
  // Release the index buffer.
  if (m_indexBuffer)
  {
    m_indexBuffer->Release();
    m_indexBuffer = nullptr;
  }

  // Release the vertex buffer.
  if (m_vertexBuffer)
  {
    m_vertexBuffer->Release();
    m_vertexBuffer = nullptr;
  }

  return;
}
