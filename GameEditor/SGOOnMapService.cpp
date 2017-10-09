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
  std::vector<SGOOnMapDbInfo> gameObjects = m_unitOfWork->GetSGOOnMapRepository()->GetAll();

  QList<SGOOnMapDbInfo> qListGameObjects;
  qListGameObjects.reserve(gameObjects.size());

  std::copy(gameObjects.begin(), gameObjects.end(), std::back_inserter(qListGameObjects));

  return  qListGameObjects;
}

void SGOOnMapService::Create(SGOOnMapDbInfo& gameObject)
{
  m_unitOfWork->GetSGOOnMapRepository()->Create(gameObject);
}

void SGOOnMapService::Update(SGOOnMapDbInfo& gameObject)
{
  m_unitOfWork->GetSGOOnMapRepository()->Update(gameObject);
}

void SGOOnMapService::Delete(int id)
{
  m_unitOfWork->GetSGOOnMapRepository()->Delete(id);
}

QList<SGOOnMapBLL> SGOOnMapService::GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string SGOName, std::string instanceName)
{
  std::vector<std::string> whereParams;
  std::string whereParamsGlue = " AND ";
  parameters.whereCondition = "";
  bool filteringIsEnabled = false;
  std::vector<SGOOnMapDbInfo> gameObjects;
  QList<SGOOnMapBLL> qListGameObjects;
 

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

  
  parameters.joinInfos.push_back(JoinInfo{ m_SGOMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  gameObjects = m_unitOfWork->GetSGOOnMapRepository()->GetAll(parameters, pagingInfo);
  qListGameObjects.reserve(gameObjects.size());
  for (auto& gameObject : gameObjects)
  {
    SGOOnMapBLL SGOOnMapBLL;
    SGOOnMapBLL.id = gameObject.id;
    SGOOnMapBLL.instanceName = gameObject.instanceName;
    SGOOnMapBLL.SGOName = gameObject.staticGameObjectDbInfo.name;
    SGOOnMapBLL.staticGameObjectId = gameObject.staticGameObjectId;

    qListGameObjects.push_back(SGOOnMapBLL);
  }

  return qListGameObjects;
}

SGOOnMapBLL SGOOnMapService::Get(int id)
{
  std::vector<JoinInfo> joinInfos;
  joinInfos.push_back(JoinInfo{ m_SGOMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  SGOOnMapDbInfo gameObject = m_unitOfWork->GetSGOOnMapRepository()->Get(id, &joinInfos);

  SGOOnMapBLL SGOOnMapBLL;
  SGOOnMapBLL.id = gameObject.id;
  SGOOnMapBLL.instanceName = gameObject.instanceName;
  SGOOnMapBLL.SGOName = gameObject.staticGameObjectDbInfo.name;
  SGOOnMapBLL.staticGameObjectId = gameObject.staticGameObjectId;

  return SGOOnMapBLL;
}