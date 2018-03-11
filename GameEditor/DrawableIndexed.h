#pragma once

#include <d3d11.h>
#include <memory>
#include <vector>
#include "Logger.h"
#include "Uncopyable.h"
#include "DirectXDeleter.h"

template <class T>
class DrawableIndexed : private Uncopyable
{
protected:
  static const unsigned int VERTEX_BUFFER_TYPE_SIZE;
  mutable int m_indexCount;
  std::unique_ptr<ID3D11Buffer, DirectXDeleter<ID3D11Buffer> > m_vertexBuffer;
  std::unique_ptr<ID3D11Buffer, DirectXDeleter<ID3D11Buffer> > m_indexBuffer;
protected:
  ID3D11Buffer* CreateVertexBuffer(ID3D11Device* device, const std::vector<T>& vertexes) const;
  ID3D11Buffer* CreateIndexBuffer(ID3D11Device* device, const std::vector<unsigned long>& indexes) const;
  void InitializeBuffers(ID3D11Device* device, const std::vector<T>& vertixes, const std::vector<unsigned long>& indexes);
public:
  DrawableIndexed();
  virtual ~DrawableIndexed() = default;
  void PrepareToRender(ID3D11DeviceContext* deviceContext) const;
  int GetIndexCount() const { return m_indexCount; }
};

template <class T>
const unsigned int DrawableIndexed<T>::VERTEX_BUFFER_TYPE_SIZE = sizeof(T);

template <class T>
DrawableIndexed<T>::DrawableIndexed()
  : m_indexCount(0),
    m_vertexBuffer(nullptr),
    m_indexBuffer(nullptr)
{

}

template <class T>
void DrawableIndexed<T>::InitializeBuffers(ID3D11Device* device, const std::vector<T>& vertixes, const std::vector<unsigned long>& indexes)
{
  m_vertexBuffer.reset(CreateVertexBuffer(device, vertixes));
  m_indexBuffer.reset(CreateIndexBuffer(device, indexes));
}

template <class T>
void DrawableIndexed<T>::PrepareToRender(ID3D11DeviceContext* deviceContext) const
{
  unsigned int stride = VERTEX_BUFFER_TYPE_SIZE;
  unsigned int offset = 0;
  auto ptr = m_vertexBuffer.get();
  deviceContext->IASetVertexBuffers(0, 1, &ptr, &stride, &offset);
  deviceContext->IASetIndexBuffer(m_indexBuffer.get(), DXGI_FORMAT_R32_UINT, 0);
}

template <class T>
ID3D11Buffer* DrawableIndexed<T>::CreateIndexBuffer(ID3D11Device* device, const std::vector<unsigned long>& indexes) const
{
  D3D11_BUFFER_DESC indexBufferDesc;
  D3D11_SUBRESOURCE_DATA indexData;
  HRESULT result;
  ID3D11Buffer* indexBuffer;

  m_indexCount = indexes.size();

  indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexes.size();
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.CPUAccessFlags = 0;
  indexBufferDesc.MiscFlags = 0;
  indexBufferDesc.StructureByteStride = 0;

  indexData.pSysMem = &indexes[0];
  indexData.SysMemPitch = 0;
  indexData.SysMemSlicePitch = 0;

  result = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
  if (FAILED(result))
    RUNTIME_ERROR("Can't create index buffer");

  return indexBuffer;
}

template <class T>
ID3D11Buffer* DrawableIndexed<T>::CreateVertexBuffer(ID3D11Device* device, const std::vector<T>& vertexes) const
{
  D3D11_BUFFER_DESC vertexBufferDesc;
  D3D11_SUBRESOURCE_DATA vertexData;
  HRESULT result;
  ID3D11Buffer* vertexBuffer;

  vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  vertexBufferDesc.ByteWidth = VERTEX_BUFFER_TYPE_SIZE * vertexes.size();
  vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  vertexBufferDesc.CPUAccessFlags = 0;
  vertexBufferDesc.MiscFlags = 0;
  vertexBufferDesc.StructureByteStride = 0;

  vertexData.pSysMem = &vertexes[0];
  vertexData.SysMemPitch = 0;
  vertexData.SysMemSlicePitch = 0;

  result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
  if (FAILED(result))
    RUNTIME_ERROR("Can't create vertex buffer ");

  return vertexBuffer;
}