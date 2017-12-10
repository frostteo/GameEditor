#include "PointLightOnMapService.h"


PointLightOnMapService::PointLightOnMapService()
{
  m_unitOfWork = BLLDependencyResolver::GetUnitOfWork();
}


PointLightOnMapService::~PointLightOnMapService()
{
}

PointLightOnMapDbInfo PointLightOnMapService::Get(int id)
{
  std::vector<JoinInfo> joinInfos;
  joinInfos.push_back(JoinInfo{ m_pointLightMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  PointLightOnMapDbInfo pointLightOnMapDbInfo = m_unitOfWork->GetPointLightOnMapRepository()->Get(id, &joinInfos);

  return pointLightOnMapDbInfo;
}

QList<PointLightOnMapDbInfo> PointLightOnMapService::GetAll()
{
  std::vector<JoinInfo> joinInfos;
  joinInfos.push_back(JoinInfo{ m_pointLightMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  joinInfos.push_back(JoinInfo{ m_sgoMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  std::vector<PointLightOnMapDbInfo> pointLightsOnMap = m_unitOfWork->GetPointLightOnMapRepository()->GetAll(&joinInfos);

  QList<PointLightOnMapDbInfo> qListpointLightsOnMap;
  qListpointLightsOnMap.reserve(pointLightsOnMap.size());

  std::copy(pointLightsOnMap.begin(), pointLightsOnMap.end(), std::back_inserter(qListpointLightsOnMap));

  return  qListpointLightsOnMap;
}

void PointLightOnMapService::IncrementPointLightCount(int id)
{
  auto pointLight = m_unitOfWork->GetPointLightRepository()->Get(id);
  pointLight.countOnMap += 1;
  m_unitOfWork->GetPointLightRepository()->Update(pointLight);
}

void PointLightOnMapService::DecrementPointLightCount(int id)
{
  auto pointLight = m_unitOfWork->GetPointLightRepository()->Get(id);
  pointLight.countOnMap -= 1;
  m_unitOfWork->GetPointLightRepository()->Update(pointLight);
}

int PointLightOnMapService::Create(PointLightOnMapDbInfo& pointLightOnMapDbInfo)
{
  int entityId = m_unitOfWork->GetPointLightOnMapRepository()->Create(pointLightOnMapDbInfo);
  IncrementPointLightCount(pointLightOnMapDbInfo.pointLightId);
  pointLightOnMapDbInfo.id = entityId;
  return entityId;
}

void PointLightOnMapService::Update(PointLightOnMapDbInfo& pointLightOnMapDbInfo)
{
  m_unitOfWork->GetPointLightOnMapRepository()->Update(pointLightOnMapDbInfo);
}

void PointLightOnMapService::Delete(int id)
{
  std::vector<JoinInfo> joinInfos;
  joinInfos.push_back(JoinInfo{ m_pointLightMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  joinInfos.push_back(JoinInfo{ m_sgoMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });

  auto pointLight = m_unitOfWork->GetPointLightOnMapRepository()->Get(id, &joinInfos);
  DecrementPointLightCount(pointLight.pointLightId);
  m_unitOfWork->GetPointLightOnMapRepository()->Delete(id);
}

QList<PointLightOnMapDbInfo> PointLightOnMapService::GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string instanceName, std::string pointLightName, std::string sgoName)
{
  std::vector<std::string> whereParams;
  std::string whereParamsGlue = " AND ";
  parameters.whereCondition = "";
  bool filteringIsEnabled = false;
  std::vector<PointLightOnMapDbInfo> gameObjects;
  QList<PointLightOnMapDbInfo> qListGameObjects;


  if (!instanceName.empty()) {
    whereParams.push_back(" PointLightOnMap_instanceName LIKE '%" + instanceName + "%' ");
    filteringIsEnabled = true;
  }

  if (!sgoName.empty()) {
    whereParams.push_back(" PointLight_name LIKE '%" + pointLightName + "%' ");
    filteringIsEnabled = true;
  }

  if (!sgoName.empty()) {
    whereParams.push_back(" StaticGameObject_name LIKE '%" + sgoName + "%' ");
    filteringIsEnabled = true;
  }

  if (filteringIsEnabled)
    parameters.whereCondition = Utils::Join(whereParams, whereParamsGlue);

  else
    parameters.whereCondition = "1";

  parameters.joinInfos.clear();
  parameters.joinInfos.push_back(JoinInfo{ m_pointLightMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  parameters.joinInfos.push_back(JoinInfo{ m_sgoMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  gameObjects = m_unitOfWork->GetPointLightOnMapRepository()->GetAll(parameters, pagingInfo);
  qListGameObjects.reserve(gameObjects.size());

  std::copy(gameObjects.begin(), gameObjects.end(), std::back_inserter(qListGameObjects));

  return qListGameObjects;
}