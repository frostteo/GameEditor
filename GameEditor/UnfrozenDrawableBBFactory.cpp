#include "UnfrozenDrawableBBFactory.h"
#include "ModelFactory.h"

UnfrozenDrawableBBFactory::UnfrozenDrawableBBFactory(ID3D11Device* device, ModelFactory* modelFactory)
  : m_device(device), m_modelFactory(modelFactory)
{
}

UnfrozenDrawableBB* UnfrozenDrawableBBFactory::GetNewResource(const std::string& filename)
{
  auto bb = m_modelFactory->GetResource(filename)->GetBoundingBox();
  UnfrozenDrawableBB* frozenDrawableBB = new UnfrozenDrawableBB(m_device, *bb);
  return frozenDrawableBB;
}
