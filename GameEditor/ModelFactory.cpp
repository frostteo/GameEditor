#include "ModelFactory.h"


ModelFactory::ModelFactory()
{
}


ModelFactory::~ModelFactory()
{
}

ModelFactory* ModelFactory::Initialize(ID3D11Device* device, ShaderFactory* shaderFactory, MaterialFactory* materialFactory)
{
  Shutdown();
  m_device = device;
  m_shaderFactory = shaderFactory;
  m_materialFactory = materialFactory;
  return this;
}

Model* ModelFactory::GetNewResource(const std::string& filename)
{
  bool result;
  Model* newModel = new Model(filename, m_device, m_materialFactory, m_shaderFactory);
  return newModel;
}