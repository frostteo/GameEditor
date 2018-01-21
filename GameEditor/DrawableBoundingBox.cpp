#include "DrawableBoundingBox.h"

const XMFLOAT3 DrawableBoundingBox::UNFROZEN_COLOR_FIRST = XMFLOAT3(1.0f, 0.0f, 0.0f);
const XMFLOAT3 DrawableBoundingBox::UNFROZEN_COLOR_SECOND = XMFLOAT3(0.0f, 1.0f, 0.0f);
const XMFLOAT3 DrawableBoundingBox::FROZEN_COLOR_FIRST = XMFLOAT3(0.043f, 0.05f, 0.5f);
const XMFLOAT3 DrawableBoundingBox::FROZEN_COLOR_SECOND = XMFLOAT3(0.013f, 0.5f, 0.1568f);

DrawableBoundingBox::DrawableBoundingBox()
{
  m_indexBuffer = nullptr;
  m_vertexBuffer = nullptr;
}

DrawableBoundingBox::~DrawableBoundingBox()
{
}

void DrawableBoundingBox::InitializeBuffers(ID3D11Device* device, bool isFrozen)
{
  if (m_indexBuffer && m_vertexBuffer && isFrozen == m_isFrozen)
    return;

  m_isFrozen = isFrozen;

  //prepare vertices
  std::vector<Vertex> vertices;
  std::vector<unsigned long> indexes;
  vertices.reserve(m_vertices.size());
  indexes.reserve(INDEX_COUNT);

  for (int i = 0; i < m_vertices.size(); ++i)
  {
    Vertex vertex;
    vertex.position = m_vertices[i];

    if (isFrozen)
    {
      if (i < 4)
        vertex.color = (i % 2 == 0 ? FROZEN_COLOR_FIRST : FROZEN_COLOR_SECOND);
      else
        vertex.color = (i % 2 == 1 ? FROZEN_COLOR_FIRST : FROZEN_COLOR_SECOND);
    }
    else
    {
      if (i < 4)
        vertex.color = (i % 2 == 0 ? UNFROZEN_COLOR_FIRST : UNFROZEN_COLOR_SECOND);
      else
        vertex.color = (i % 2 == 1 ? UNFROZEN_COLOR_FIRST : UNFROZEN_COLOR_SECOND);
    }

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

void DrawableBoundingBox::ShutdownBuffers()
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

void DrawableBoundingBox::PrepareToRender(ID3D11DeviceContext* deviceContext)
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

void DrawableBoundingBox::Initialize(BoundingBox* boundingBox)
{
  m_vertices = std::vector<XMFLOAT3>(*boundingBox->GetVertices());
}