#include "StaticGOService.h"


StaticGOService::StaticGOService()
{
  m_unitOfWork = BLLDependencyResolver::GetUnitOfWork();
}


StaticGOService::~StaticGOService()
{
}

QList<StaticGameObjectDbInfo> StaticGOService::GetStaticGameObjects()
{
  std::vector<StaticGameObjectDbInfo> gameObjects = m_unitOfWork->GetStaticGORepository()->GetAll();

  QList<StaticGameObjectDbInfo> qListGameObjects;
  qListGameObjects.reserve(gameObjects.size());

  std::copy(gameObjects.begin(), gameObjects.end(), std::back_inserter(qListGameObjects));

  return qListGameObjects;
}

void StaticGOService::CreateStaticGameObject(StaticGameObjectDbInfo& gameObject)
{
  m_unitOfWork->GetStaticGORepository()->Create(gameObject);
}

void StaticGOService::UpdateStaticGameObject(StaticGameObjectDbInfo& gameObject)
{
  m_unitOfWork->GetStaticGORepository()->Update(gameObject);
}

void StaticGOService::DeleteStaticGameObject(int id)
{
  m_unitOfWork->GetStaticGORepository()->Delete(id);
}

QList<StaticGameObjectDbInfo> StaticGOService::GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string name, std::string model, std::string material)
{
  std::vector<std::string> whereParams;
  std::string whereParamsGlue = " AND ";
  parameters.whereCondition = "";
  int index = 0;
  bool filteringIsEnabled = false;
  std::vector<StaticGameObjectDbInfo> gameObjects;
  QList<StaticGameObjectDbInfo> qListGameObjects;

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