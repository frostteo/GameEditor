#pragma once

#include <d3d11.h>
#include <string>
#include "Singleton.h"
#include "SharedResourcesFactory.h"
#include "Mesh.h"

class MeshFactory : public SharedResourcesFactory<Mesh>
{
private:
  ID3D11Device* m_device;
protected:
  Mesh* GetNewResource(const std::string& filename) override;
public:
  MeshFactory();
  virtual ~MeshFactory();
  MeshFactory* SetDevice(ID3D11Device* device)
  {
    Shutdown();
    m_device = device;
    return this;
  }
};

