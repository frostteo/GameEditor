#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include "IMaterial.h"
#include "IShader.h"
#include "ShaderFactory.h"
#include "LightininigSystem.h"
#include "ShaderFactory.h"

class Static :
  public GameObject
{
public:
  IMaterial* m_material;
  Mesh* m_mesh;
  IShader* m_shader;
public:
  Static();
  virtual ~Static();
  void Initialize(Mesh* mesh, IMaterial* material, ShaderFactory* shaderFactory) { m_mesh = mesh; m_material = material; InitializeShader(shaderFactory); }
  void SetMaterial(IMaterial* material, ShaderFactory* shaderFactory);
  void SetMesh(Mesh* mesh);
  void InitializeShader(ShaderFactory* shaderFactory);
  void Render(ID3D11DeviceContext* deviceContext, XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix, LightininigSystem* lightining, XMFLOAT3& cameraPostion);
};

