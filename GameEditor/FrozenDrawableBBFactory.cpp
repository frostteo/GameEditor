#include "FrozenDrawableBBFactory.h"
#include "ModelFactory.h"

FrozenDrawableBBFactory::FrozenDrawableBBFactory(ID3D11Device* device, ModelFactory* modelFactory) 
  : m_device(device), m_modelFactory(modelFactory)
{
}

FrozenDrawableBB* FrozenDrawableBBFactory::GetNewResource(const std::string& filename)
{
  auto bb = m_modelFactory->GetResource(filename)->GetBoundingBox();
  FrozenDrawableBB* frozenDrawableBB = new FrozenDrawableBB(m_device, *bb);
  return frozenDrawableBB;
}
