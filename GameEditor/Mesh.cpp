#include "Mesh.h"
#include "Logger.h"

Mesh::Mesh(ID3D11Device* device,
  std::string gameObjectName,
  std::string materialName,
  std::vector<VertexInBuffer>& vertices,
  std::vector<unsigned long>& indexes,
  MaterialFactory* materialFactory)
{
  m_gameObjectName = gameObjectName;
  SetMaterial(materialName, materialFactory);
  InitializeBuffers(device, vertices, indexes);
}

void Mesh::InitializeBuffers(ID3D11Device* device, std::vector<VertexInBuffer>& vertices, std::vector<unsigned long>& indexes)
{
  D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
  D3D11_SUBRESOURCE_DATA vertexData, indexData;
  HRESULT result;

  m_indexCount = indexes.size();

  // Set up the description of the static vertex buffer.
  vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  vertexBufferDesc.ByteWidth = sizeof(VertexInBuffer) * vertices.size();
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
    RUNTIME_ERROR("Can't create vertex buffer for mesh of " + m_gameObjectName + " with material " + m_materialName);

  // Set up the description of the static index buffer.
  indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
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
    RUNTIME_ERROR("Can't create index buffer" + m_gameObjectName + " with material " + m_materialName);
}

void Mesh::SetMaterial(std::string materialName, MaterialFactory* materialFactory)
{
  m_materialName = materialName;
  m_material = materialFactory->GetResource(materialName);
  m_materialType = m_material->GetType();
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
}

void Mesh::PrepareToRender(ID3D11DeviceContext* deviceContext)
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
}

Mesh::~Mesh()
{
  ShutdownBuffers();
}
