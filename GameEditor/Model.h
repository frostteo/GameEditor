#pragma once

#include "SubMesh.h"
#include "GameObject.h"
#include "FileProcessor.h"
#include "ObjMeshConverter.h"

class Model : public GameObject
{
protected:
  std::string m_fileName;
  std::vector<SubMesh*> m_submeshes;
protected:
  void LoadData(
    ID3D11Device* device,
    MaterialFactory* materialFactory,
    ShaderFactory* shaderFactory
    );

  void LoadSubMesh(
    std::stringstream& stream,
    ID3D11Device* device,
    MaterialFactory* materialFactory,
    ShaderFactory* shaderFactory
    );

public:
  Model(
    std::string fileName,
    ID3D11Device* device,
    MaterialFactory* materialFactory,
    ShaderFactory* shaderFactory
    );

  void Render(ID3D11DeviceContext* deviceContext, XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix, LightininigSystem* lightining, XMFLOAT3& cameraPostion);
  virtual ~Model();
};

