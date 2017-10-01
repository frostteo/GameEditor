#pragma once

#include <vector>
#include <string>
#include <d3d11.h>
#include <directxmath.h>
#include "Logger.h"
#include "IMaterial.h"
#include "MaterialFactory.h"

using namespace DirectX;

class Mesh
{
public:
  struct VertexInBuffer
  {
    XMFLOAT3 position;
    XMFLOAT2 texture;
    XMFLOAT3 normal;
    XMFLOAT3 tangent;
    XMFLOAT3 binormal;
  };
private:
  std::string m_gameObjectName;
  std::string m_materialName;
  std::string m_materialType;
  int m_indexCount;
  ID3D11Buffer* m_vertexBuffer;
  ID3D11Buffer* m_indexBuffer;
  IMaterial* m_material;
protected:
  void ShutdownBuffers();
public:
  Mesh(ID3D11Device* device,
    std::string gameObjectName, 
    std::string materialName,
    std::vector<VertexInBuffer>& vertices, 
    std::vector<unsigned long>& indexes,
    MaterialFactory* materialFactory);

  void InitializeBuffers(ID3D11Device* device, std::vector<VertexInBuffer>& vertices, std::vector<unsigned long>& indexes);
  void SetMaterial(std::string materialName, MaterialFactory* materialFactory);
  IMaterial* GetMaterial() { return m_material; }
  const std::string GetMaterialName() { return m_materialName; }
  const std::string GetMaterialType() { return m_materialType; }
  void PrepareToRender(ID3D11DeviceContext* deviceContext);
  int GetIndexCount() { return m_indexCount; }
  virtual ~Mesh();
};

