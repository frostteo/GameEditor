#include "Mesh.h"
#include "Logger.h"

Mesh::Mesh(ID3D11Device* device,
  std::string gameObjectName,
  std::vector<MeshVertex>& vertixes,
  std::vector<unsigned long>& indexes,
  IMaterial* material)
  : m_gameObjectName(gameObjectName),
    m_material(material)
{
  InitializeBuffers(device, vertixes, indexes);
}