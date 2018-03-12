#pragma once

#include <string>
#include <vector>
#include <memory>
#include <d3d11.h>
#include <directxmath.h>
#include "Uncopyable.h"

class Logger;
class FileProcessor;
class MaterialFactory;
class VertexTxt;
class BoundingBox;
class Mesh;

using namespace DirectX;

class Model : private Uncopyable
{
protected:
  const std::string m_fileName;
  std::vector<std::unique_ptr<Mesh> > m_meshes;
  std::unique_ptr<BoundingBox> m_boundingBox;
protected:
  void LoadModel(
    ID3D11Device* device,
    MaterialFactory& materialFactory
    );

  void LoadMesh(
    std::stringstream& stream,
    ID3D11Device* device,
    MaterialFactory& materialFactory
    );

public:
  Model(
    std::string fileName,
    ID3D11Device* device,
    MaterialFactory& materialFactory
    );

  const Mesh* GetMesh(int index) const { return m_meshes[index].get(); }
  int GetMeshCount() const { return m_meshes.size(); }
  const BoundingBox* GetBoundingBox() const { return m_boundingBox.get(); }
  virtual ~Model();
  const std::string GetName() const { return m_fileName; }
};

