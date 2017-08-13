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

QList<StaticGameObject> StaticGOService::GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string name, std::string model, std::string material)
{
  std::vector<std::string> whereParams;
  std::string whereParamsGlue = " AND ";
  parameters.whereCondition = "";
  int index = 0;
  bool filteringIsEnabled = false;
  std::vector<StaticGameObject> gameObjects;
  QList<StaticGameObject> qListGameObjects;

  if (!name.empty()) {
    whereParams.push_back(" name LIKE '%" + name + "%' ");
    filteringIsEnabled = true;
  }


  if (!model.empty()) {
    whereParams.push_back(" modelFileName LIKE '%" + model + "%' ");
    filteringIsEnabled = true;
  }

  if (!material.empty()) {
    whereParams.push_back(" materialFileName LIKE '%" + material + "%' ");
    filteringIsEnabled = true;
  }

  if (filteringIsEnabled)
    parameters.whereCondition = Utils::Join(whereParams, whereParamsGlue);

  else
    parameters.whereCondition = "1";

  gameObjects = m_unitOfWork->GetStaticGORepository()->GetAll(parameters, pagingInfo);
  qListGameObjects.reserve(gameObjects.size());
  std::copy(gameObjects.begin(), gameObjects.end(), std::back_inserter(qListGameObjects));

  return qListGameObjects;
}