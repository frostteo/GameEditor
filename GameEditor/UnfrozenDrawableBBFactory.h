#pragma once

#include <d3d11.h>
#include "SharedResourcesFactory.h"
#include "UnfrozenDrawableBB.h"

class ModelFactory;

class UnfrozenDrawableBBFactory : public SharedResourcesFactory<UnfrozenDrawableBB>
{
private:
  ID3D11Device* m_device;
  ModelFactory* m_modelFactory;
protected:
  UnfrozenDrawableBB* GetNewResource(const std::string& filename) override;
public:
  UnfrozenDrawableBBFactory(ID3D11Device* device, ModelFactory* modelFactory);
  virtual ~UnfrozenDrawableBBFactory() = default;
};

