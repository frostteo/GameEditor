#pragma once

#include <vector>
#include <string>
#include <d3d11.h>
#include <directxmath.h>
#include "Logger.h"
#include "IMaterial.h"
#include "IShader.h"
#include "ShaderFactory.h"
#include "MaterialFactory.h"
#include "LightininigSystem.h"

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
  int m_indexCount;
  ID3D11Buffer* m_vertexBuffer;
  ID3D11Buffer* m_indexBuffer;
  IMaterial* m_material;
  IShader* m_shader;
protected:
  void ShutdownBuffers();
  int GetIndexCount() { return m_indexCount; } //FHolod: later will be removed
public:
  Mesh(ID3D11Device* device,
    std::string gameObjectName, 
    std::string materialName,
    std::vector<VertexInBuffer>& vertices, 
    std::vector<unsigned long>& indexes,
    MaterialFactory* materialFactory,
    ShaderFactory* shaderFactory);

  void InitializeBuffers(ID3D11Device* device, std::vector<VertexInBuffer>& vertices, std::vector<unsigned long>& indexes);
  void SetMaterial(std::string materialName, MaterialFactory* materialFactory);
  void InitializeShader(ShaderFactory* shaderFactory);
  void Render(ID3D11DeviceContext* deviceContext, XMMATRIX& worldMatrix, XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix, LightininigSystem* lightining, XMFLOAT3& cameraPostion);
  virtual ~Mesh();
};

