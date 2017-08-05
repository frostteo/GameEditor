#include "StaticGOService.h"


StaticGOService::StaticGOService()
{
  m_unitOfWork = BLLDependencyResolver::GetUnitOfWork();
}


StaticGOService::~StaticGOService()
{
}

QList<StaticGameObject> StaticGOService::GetStaticGameObjects()
{
  std::vector<StaticGameObject> gameObjects = m_unitOfWork->GetStaticGORepository()->GetAll();

  QList<StaticGameObject> qListGameObjects;
  qListGameObjects.reserve(gameObjects.size());

  std::copy(gameObjects.begin(), gameObjects.end(), std::back_inserter(qListGameObjects));

  return qListGameObjects;
}

void StaticGOService::CreateStaticGameObject(StaticGameObject& gameObject)
{
  m_unitOfWork->GetStaticGORepository()->Create(gameObject);
}

void StaticGOService::UpdateStaticGameObject(StaticGameObject& gameObject)
{
  m_unitOfWork->GetStaticGORepository()->Update(gameObject);
}

void StaticGOService::DeleteStaticGameObject(int id)
{
  m_unitOfWork->GetStaticGORepository()->Delete(id);
}