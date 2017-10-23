#include "SGOOnMapService.h"


SGOOnMapService::SGOOnMapService()
{
  m_unitOfWork = BLLDependencyResolver::GetUnitOfWork();
}


SGOOnMapService::~SGOOnMapService()
{
}

QList<SGOOnMapDbInfo> SGOOnMapService::GetAll()
{
  std::vector<JoinInfo> joinInfos;
  joinInfos.push_back(JoinInfo{ m_SGOMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  std::vector<SGOOnMapDbInfo> gameObjects = m_unitOfWork->GetSGOOnMapRepository()->GetAll(&joinInfos);

  QList<SGOOnMapDbInfo> qListGameObjects;
  qListGameObjects.reserve(gameObjects.size());

  std::copy(gameObjects.begin(), gameObjects.end(), std::back_inserter(qListGameObjects));

  return  qListGameObjects;
}

int SGOOnMapService::Create(SGOOnMapDbInfo& gameObject)
{
  int entityId = m_unitOfWork->GetSGOOnMapRepository()->Create(gameObject);
  IncrementSGOCount(gameObject.staticGameObjectId);
  gameObject.id = entityId;
  return entityId;
}

void SGOOnMapService::Update(SGOOnMapDbInfo& gameObject)
{
  m_unitOfWork->GetSGOOnMapRepository()->Update(gameObject);
}

void SGOOnMapService::Delete(int id)
{
  auto gameObject = m_unitOfWork->GetSGOOnMapRepository()->Get(id);
  DecrementSGOCount(gameObject.staticGameObjectId);
  m_unitOfWork->GetSGOOnMapRepository()->Delete(id);
}

QList<SGOOnMapDbInfo> SGOOnMapService::GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string SGOName, std::string instanceName)
{
  std::vector<std::string> whereParams;
  std::string whereParamsGlue = " AND ";
  parameters.whereCondition = "";
  bool filteringIsEnabled = false;
  std::vector<SGOOnMapDbInfo> gameObjects;
  QList<SGOOnMapDbInfo> qListGameObjects;
 

  if (!SGOName.empty()) {
    whereParams.push_back(" StaticGameObjectDbInfo_name LIKE '%" + SGOName + "%' ");
    filteringIsEnabled = true;
  }


  if (!instanceName.empty()) {
    whereParams.push_back(" SGOOnMapDbInfo_instanceName LIKE '%" + instanceName + "%' ");
    filteringIsEnabled = true;
  }

  if (filteringIsEnabled)
    parameters.whereCondition = Utils::Join(whereParams, whereParamsGlue);

  else
    parameters.whereCondition = "1";

  parameters.joinInfos.clear();
  parameters.joinInfos.push_back(JoinInfo{ m_SGOMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  gameObjects = m_unitOfWork->GetSGOOnMapRepository()->GetAll(parameters, pagingInfo);
  qListGameObjects.reserve(gameObjects.size());

  std::copy(gameObjects.begin(), gameObjects.end(), std::back_inserter(qListGameObjects));

  return qListGameObjects;
}

SGOOnMapDbInfo SGOOnMapService::Get(int id)
{
  std::vector<JoinInfo> joinInfos;
  joinInfos.push_back(JoinInfo{ m_SGOMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  SGOOnMapDbInfo gameObject = m_unitOfWork->GetSGOOnMapRepository()->Get(id, &joinInfos);

  return gameObject;
}

void SGOOnMapService::IncrementSGOCount(int id)
{
  auto gameObject = m_unitOfWork->GetStaticGORepository()->Get(id);
  gameObject.countOnMap += 1;
  m_unitOfWork->GetStaticGORepository()->Update(gameObject);
}

void SGOOnMapService::DecrementSGOCount(int id)
{
  auto gameObject = m_unitOfWork->GetStaticGORepository()->Get(id);
  gameObject.countOnMap -= 1;
  m_unitOfWork->GetStaticGORepository()->Update(gameObject);
}