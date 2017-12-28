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
  joinInfos.push_back(JoinInfo{ m_sgoMetadata.GetTableName().toStdString(), JoinOperator::LEFT_JOIN });
  joinInfos.push_back(JoinInfo{ m_sgoOnMapMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  PointLightOnMapDbInfo pointLightOnMapDbInfo = m_unitOfWork->GetPointLightOnMapRepository()->Get(id, &joinInfos);

  return pointLightOnMapDbInfo;
}

PointLightOnMapDbInfo PointLightOnMapService::GetBySgoOnMapId(int id)
{
  GetParameters parameters;
  PagingInfo pagingInfo;
  std::vector<PointLightOnMapDbInfo> gameObjects;

  parameters.whereCondition = (QString("%1 = %2").arg(m_pointLightOnMapMetadata.GetAlias(1), QString::number(id))).toStdString();

  parameters.joinInfos.clear();
  parameters.joinInfos.push_back(JoinInfo{ m_pointLightMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  parameters.joinInfos.push_back(JoinInfo{ m_sgoMetadata.GetTableName().toStdString(), JoinOperator::LEFT_JOIN });
  parameters.joinInfos.push_back(JoinInfo{ m_sgoOnMapMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  gameObjects = m_unitOfWork->GetPointLightOnMapRepository()->GetAll(parameters, pagingInfo);

  return gameObjects[0];
}

QList<PointLightOnMapDbInfo> PointLightOnMapService::GetAll()
{
  std::vector<JoinInfo> joinInfos;
  joinInfos.push_back(JoinInfo{ m_pointLightMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  joinInfos.push_back(JoinInfo{ m_sgoMetadata.GetTableName().toStdString(), JoinOperator::LEFT_JOIN });
  joinInfos.push_back(JoinInfo{ m_sgoOnMapMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
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
  auto pointLight = m_unitOfWork->GetPointLightOnMapRepository()->Get(id);
  DecrementPointLightCount(pointLight.pointLightId);
  m_unitOfWork->GetPointLightOnMapRepository()->Delete(id);
}

QList<PointLightOnMapDbInfo> PointLightOnMapService::GetByPointLightId(int id)
{
  GetParameters parameters;
  PagingInfo pagingInfo;
  std::vector<PointLightOnMapDbInfo> gameObjects;
  QList<PointLightOnMapDbInfo> qListpointLightsOnMap;
  parameters.onPage = INT_MAX;

  parameters.whereCondition = QString("%1 = %2").arg(m_pointLightOnMapMetadata.GetAlias(0), QString::number(id)).toStdString();

  parameters.joinInfos.clear();
  parameters.joinInfos.push_back(JoinInfo{ m_pointLightMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  parameters.joinInfos.push_back(JoinInfo{ m_sgoMetadata.GetTableName().toStdString(), JoinOperator::LEFT_JOIN });
  parameters.joinInfos.push_back(JoinInfo{ m_sgoOnMapMetadata.GetTableName().toStdString(), JoinOperator::INNER_JOIN });
  gameObjects = m_unitOfWork->GetPointLightOnMapRepository()->GetAll(parameters, pagingInfo);

  qListpointLightsOnMap.reserve(gameObjects.size());
  std::copy(gameObjects.begin(), gameObjects.end(), std::back_inserter(qListpointLightsOnMap));
  return  qListpointLightsOnMap;
}

StaticGameObjectDbInfo PointLightOnMapService::GetDefaultPointLightSgo()
{
  return m_unitOfWork->GetStaticGORepository()->Get(DEFAUT_POINT_LIGHT_SGO);
}