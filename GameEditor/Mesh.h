#pragma once

#include <vector>
#include <string>
#include <d3d11.h>
#include <directxmath.h>
#include "DrawableIndexed.h"
#include "IMaterial.h"

class Logger;

using namespace DirectX;

struct MeshVertex
{
  XMFLOAT3 position;
  XMFLOAT2 texture;
  XMFLOAT3 normal;
  XMFLOAT3 tangent;
  XMFLOAT3 binormal;
};

class Mesh : public DrawableIndexed<MeshVertex>
{
private:
  std::string m_gameObjectName;
  IMaterial* m_material;
public:
  Mesh(ID3D11Device* device,
    std::string gameObjectName, 
    std::vector<MeshVertex>& vertices,
    std::vector<unsigned long>& indexes,
    IMaterial* material);

  void SetMaterial(IMaterial* material) { m_material = material; }
  const IMaterial* GetMaterial() const { return m_material; }
  const std::string GetMaterialName() const { return m_material->GetName(); }
  const std::string GetMaterialType() const { return m_material->GetType(); }
  virtual ~Mesh() = default;
};

