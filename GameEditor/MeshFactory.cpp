#include "MeshFactory.h"


MeshFactory::MeshFactory()
{
}

MeshFactory::~MeshFactory()
{
 
}

Mesh* MeshFactory::GetNewResource(const std::string& filename)
{
  bool result;
  Mesh* newMesh = new Mesh();
  result = newMesh->Initialize(m_device, filename);
  if (!result) {
    Logger::get().LogMessageWithExceptionDialog("cant initialize mesh " + filename, __FILE__, __LINE__);
  }

  return newMesh;
}