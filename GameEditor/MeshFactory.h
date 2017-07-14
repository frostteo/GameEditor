#pragma once

#include <d3d11.h>
#include <string>
#include "Singleton.h"
#include "SharedResourcesFactory.h"
#include "Mesh.h"

class MeshFactory : public SharedResourcesFactory<Mesh>, public Singleton<MeshFactory>
{
  friend class Singleton<MeshFactory>;
private:
  ID3D11Device* m_device;
protected:
  MeshFactory();
  virtual ~MeshFactory();
  Mesh* GetNewResource(const std::string& filename) override;
public:
  void SetDevice(ID3D11Device* device)
  {
    m_device = device;
  }
};

