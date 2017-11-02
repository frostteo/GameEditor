#include "BoundingBox.h"

const char BoundingBox::BOUNDING_BOX_SERIALIZE_NAME[BOUNDING_BOX_SERIALIZE_NAME_LENGTH] = "bounding box: ";

BoundingBox::BoundingBox()
{
  m_indexBuffer = nullptr;
  m_vertexBuffer = nullptr;
}

void BoundingBox::Initialize(float& minX, float& minY, float& minZ, float& maxX, float& maxY, float& maxZ)
{
  const int countOfPointInParallelepiped = 8;

  m_minPoint = XMFLOAT3(minX, minY, minZ);
  m_maxPoint = XMFLOAT3(maxX, maxY, maxZ);

  VertexPosition bottomNearLeft = { minX, minY, minZ };
  VertexPosition bottomFarLeft = { minX, minY, maxZ };
  VertexPosition bottomFarRight = { maxX, minY, maxZ };
  VertexPosition bottomNearRight = { maxX, minY, minZ };
  VertexPosition topNearLeft = { minX, maxY, minZ };
  VertexPosition topFarLeft = { minX, maxY, maxZ };
  VertexPosition topFarRight = { maxX, maxY, maxZ };
  VertexPosition topNearRight = { maxX, maxY, minZ };

  m_vertices.clear();
  m_vertices.reserve(countOfPointInParallelepiped);
  m_vertices.push_back(bottomNearLeft);
  m_vertices.push_back(bottomFarLeft);
  m_vertices.push_back(bottomFarRight);
  m_vertices.push_back(bottomNearRight);
  m_vertices.push_back(topNearLeft);
  m_vertices.push_back(topFarLeft);
  m_vertices.push_back(topFarRight);
  m_vertices.push_back(topNearRight);
}

void BoundingBox::SerializeStatic(std::ostream& ostream, float& minX, float& minY, float& minZ, float& maxX, float& maxY, float& maxZ)
{
  char space = ' ';
  ostream << BOUNDING_BOX_SERIALIZE_NAME;
  ostream << minX << space << minY << space << minZ << space;
  ostream << maxX << space << maxY << space << maxZ << std::endl;
}

void BoundingBox::Serialize(std::ostream& ostream)
{
  SerializeStatic(ostream, m_vertices[0].x, m_vertices[0].y, m_vertices[0].z, m_vertices[6].x, m_vertices[6].y, m_vertices[6].z);
}

void BoundingBox::Deserialize(std::istream& istream)
{
  float minX, minY, minZ, maxX, maxY, maxZ;

  char space[BOUNDING_BOX_SERIALIZE_NAME_LENGTH];
  istream.read(space, BOUNDING_BOX_SERIALIZE_NAME_LENGTH - 1);

  if (strncmp(space, BOUNDING_BOX_SERIALIZE_NAME, BOUNDING_BOX_SERIALIZE_NAME_LENGTH - 1))
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("Cant read bounding box from stream", __FILE__, __LINE__));

  istream >> minX >> minY >> minZ >> maxX >> maxY >> maxZ;
  Initialize(minX, minY, minZ, maxX, maxY, maxZ);
}

BoundingBox::~BoundingBox()
{
}


void BoundingBox::InitializeBuffers(ID3D11Device* device)
{
  if (m_indexBuffer && m_vertexBuffer)
    return;

  //prepare vertices
  std::vector<Vertex> vertices;
  std::vector<unsigned long> indexes;
  vertices.reserve(m_vertices.size());
  indexes.reserve(INDEX_COUNT);

  for (int i = 0; i < m_vertices.size(); ++i)
  {
    Vertex vertex;
    vertex.position = XMFLOAT3(m_vertices[i].x, m_vertices[i].y, m_vertices[i].z);
    if (i < 4)
      vertex.color = (i % 2 == 0 ? XMFLOAT3(1.0f, 0.0f, 0.0f) : XMFLOAT3(0.0f, 1.0f, 0.0f));
    else
      vertex.color = (i % 2 == 1 ? XMFLOAT3(1.0f, 0.0f, 0.0f) : XMFLOAT3(0.0f, 1.0f, 0.0f));

    vertices.push_back(vertex);
  }

  //prepare indecex
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
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("Can't create vertex buffer for bounding box", __FILE__, __LINE__));

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
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("Can't create index buffer for bounding box", __FILE__, __LINE__));
}

void BoundingBox::ShutdownBuffers()
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

void BoundingBox::PrepareToRender(ID3D11DeviceContext* deviceContext)
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

XMFLOAT3 BoundingBox::GetMinPoint()
{
  return m_minPoint;
}

XMFLOAT3 BoundingBox::GetMaxPoint()
{
  return m_maxPoint;
}