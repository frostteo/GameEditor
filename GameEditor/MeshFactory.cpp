#include "MeshFactory.h"


MeshFactory::MeshFactory()
{
}

MeshFactory::~MeshFactory()
{
 
}

Mesh* MeshFactory::GetNewResource(const std::string& filename)
{
  Mesh* newMesh = new Mesh();
  newMesh->Initialize(m_device, filename);
  return newMesh;
}