#pragma once

#include "Mesh.h"
#include "GameObject.h"
#include "FileProcessor.h"
#include "VertexTxt.h"
#include "BoundingBox.h"

class BoundingBox;

class Model : public GameObject
{
protected:
  std::string m_fileName;
  std::vector<Mesh*> m_meshes;
  BoundingBox m_boundingBox;
protected:
  void LoadData(
    ID3D11Device* device,
    MaterialFactory* materialFactory
    );

  void LoadMesh(
    std::stringstream& stream,
    ID3D11Device* device,
    MaterialFactory* materialFactory
    );

public:
  Model(
    std::string fileName,
    ID3D11Device* device,
    MaterialFactory* materialFactory
    );

  Mesh* GetMesh(int index) { return m_meshes[index]; }
  const int GetMeshCount() { return m_meshes.size(); }
  BoundingBox* GetBoundingBox() { return &m_boundingBox; }
  virtual ~Model();
};

