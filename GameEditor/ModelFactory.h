#pragma once

#include "SharedResourcesFactory.h"
#include "Model.h"

class MaterialFactory;

class ModelFactory : public SharedResourcesFactory<Model>
{
private:
  ID3D11Device* m_device;
  MaterialFactory* m_materialFactory;
protected:
  Model* GetNewResource(const std::string& filename) override;
public:
  ModelFactory();
  virtual ~ModelFactory();
  ModelFactory* Initialize(ID3D11Device* device, MaterialFactory* materialFactory);
};

