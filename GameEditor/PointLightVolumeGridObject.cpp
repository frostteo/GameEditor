#include "PointLightVolumeGridObject.h"
#include "Logger.h"

const XMFLOAT3 PointLightVolumeGridObject::LIGHT_COLOR = XMFLOAT3(1.0f, 0.5f, 0.0f);

PointLightVolumeGridObject::PointLightVolumeGridObject()
{
  float min = -1;
  float max = 1;

  XMFLOAT3 bottomNearLeft = { min, min, min };
  XMFLOAT3 bottomFarLeft = { min, min, max };
  XMFLOAT3 bottomFarRight = { max, min, max };
  XMFLOAT3 bottomNearRight = { max, min, min };
  XMFLOAT3 topNearLeft = { min, max, min };
  XMFLOAT3 topFarLeft = { min, max, max };
  XMFLOAT3 topFarRight = { max, max, max };
  XMFLOAT3 topNearRight = { max, max, min };

  m_vertexPositions.clear();
  m_vertexPositions.reserve(COUNT_OF_POINTS);
  m_vertexPositions.push_back(bottomNearLeft);
  m_vertexPositions.push_back(bottomFarLeft);
  m_vertexPositions.push_back(bottomFarRight);
  m_vertexPositions.push_back(bottomNearRight);
  m_vertexPositions.push_back(topNearLeft);
  m_vertexPositions.push_back(topFarLeft);
  m_vertexPositions.push_back(topFarRight);
  m_vertexPositions.push_back(topNearRight);

  m_indexBuffer = nullptr;
  m_vertexBuffer = nullptr;
}


PointLightVolumeGridObject::~PointLightVolumeGridObject()
{
  ShutdownBuffers();
}

void PointLightVolumeGridObject::InitializeBuffers(ID3D11Device* device)
{
  if (m_indexBuffer && m_vertexBuffer)
    return;

  std::vector<Vertex> vertices;
  std::vector<unsigned long> indexes;
  vertices.reserve(m_vertexPositions.size());
  indexes.reserve(INDEX_COUNT);

  for (auto position : m_vertexPositions)
  {
    Vertex vertex;
    vertex.position = position;
    vertex.color = LIGHT_COLOR;
    vertices.push_back(vertex);
  }

  //prepare indexes
  //bottom
  indexes.push_back(0);
  indexes.push_back(3);
  indexes.push_back(3);
  indexes.push_back(2);
  indexes.push_back(2);
  indexes.push_back(1);
  indexes.push_back(1);
  indexes.push_back(0);

  //top face
  indexes.push_back(4);
  indexes.push_back(5);
  indexes.push_back(5);
  indexes.push_back(6);
  indexes.push_back(6);
  indexes.push_back(7);
  indexes.push_back(7);
  indexes.push_back(4);

  //sides
  indexes.push_back(0);
  indexes.push_back(4);
  indexes.push_back(7);
  indexes.push_back(3);
  indexes.push_back(6);
  indexes.push_back(2);
  indexes.push_back(1);
  indexes.push_back(5);

  D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
  D3D11_SUBRESOURCE_DATA vertexData, indexData;
  HRESULT result;

  // Set up the description of the static vertex buffer.
  vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
  vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  vertexBufferDesc.CPUAccessFlags = 0;
  vertexBufferDesc.MiscFlags = 0;
  vertexBufferDesc.StructureByteStride = 0;

  // Give the subresource structure a pointer to the vertex data.
  vertexData.pSysMem = &vertices[0];
  vertexData.SysMemPitch = 0;
  vertexData.SysMemSlicePitch = 0;

  // Now create the vertex buffer.
  result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
  if (FAILED(result))
    RUNTIME_ERROR("Can't create vertex buffer for point light volume grid object");

  // Set up the description of the static index buffer.
  indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  indexBufferDesc.ByteWidth = sizeof(unsigned long) * INDEX_COUNT;
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.CPUAccessFlags = 0;
  indexBufferDesc.MiscFlags = 0;
  indexBufferDesc.StructureByteStride = 0;

  // Give the subresource structure a pointer to the index data.
  indexData.pSysMem = &indexes[0];
  indexData.SysMemPitch = 0;
  indexData.SysMemSlicePitch = 0;

  // Create the index buffer.
  result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
  if (FAILED(result))
    RUNTIME_ERROR("Can't create index buffer for point light volume grid object");
}

void PointLightVolumeGridObject::PrepareToRender(ID3D11DeviceContext* deviceContext)
{
  unsigned int stride;
  unsigned int offset;

  // Set vertex buffer stride and offset.
  stride = sizeof(Vertex);
  offset = 0;

  // Set the vertex buffer to active in the input assembler so it can be rendered.
  deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

  // Set the index buffer to active in the input assembler so it can be rendered.
  deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void PointLightVolumeGridObject::ShutdownBuffers()
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
}