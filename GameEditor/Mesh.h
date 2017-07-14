#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <fstream>
#include <string>
#include "Logger.h"

#include "ObjMeshConverter.h"

using namespace DirectX;

class Mesh
{
private:
  struct VertexInBuffer
  {
    XMFLOAT3 position;
    XMFLOAT2 texture;
    XMFLOAT3 normal;
    XMFLOAT3 tangent;
    XMFLOAT3 binormal;
  };
private:
  ID3D11Buffer* m_vertexBuffer;
  ID3D11Buffer* m_indexBuffer;
  std::string m_fileName;
  std::vector<VertexInBuffer> m_vertices;
  std::vector<unsigned long> m_indexes;
protected:
  bool LoadMesh(); 
  bool InitializeBuffers(ID3D11Device* device);
  void ShutdownBuffers();
public:
  Mesh();
  virtual ~Mesh();

  bool Initialize(ID3D11Device* device, const std::string& meshFileName);
  void Render(ID3D11DeviceContext* deviceContext);
  void Shutdown();
  int GetIndexCount() { return m_indexes.size(); }
  bool operator< (const Mesh& other) const
  {
    return this->m_fileName < other.m_fileName;
  }
  bool operator== (const Mesh& other) const
  {
    return this->m_fileName == other.m_fileName;
  }
  const std::string& GetName() const {
    return m_fileName;
  }
};

