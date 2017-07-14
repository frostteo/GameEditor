#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include "IMaterial.h"
#include "IShader.h"
#include "ShaderFactory.h"

class Static :
  public GameObject
{
protected:
  IMaterial* m_material;
  Mesh* m_mesh;
  IShader* m_shader;
public:
  Static();
  virtual ~Static();
  void Initialize(Mesh* mesh, IMaterial* material) { m_mesh = mesh; m_material = material; InitializeShader(); }
  void SetMaterial(IMaterial* material);
  void SetMesh(Mesh* mesh);
  void InitializeShader();
  void Render(ID3D11DeviceContext* deviceContext, XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix);
};

