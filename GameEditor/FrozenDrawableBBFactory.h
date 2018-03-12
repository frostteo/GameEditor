#pragma once

#include <d3d11.h>
#include "SharedResourcesFactory.h"
#include "FrozenDrawableBB.h"

class ModelFactory;

class FrozenDrawableBBFactory : public SharedResourcesFactory<FrozenDrawableBB>
{
private:
  ID3D11Device* m_device;
  ModelFactory* m_modelFactory;
protected:
  FrozenDrawableBB* GetNewResource(const std::string& filename) override;
public:
  FrozenDrawableBBFactory(ID3D11Device* device, ModelFactory* modelFactory);
  virtual ~FrozenDrawableBBFactory() = default;
};

