#include "PointLightService.h"


PointLightService::PointLightService()
  : m_unitOfWork(BLLDependencyResolver::GetUnitOfWork())
{
}


PointLightService::~PointLightService()
{
}

PointLightDbInfo PointLightService::Get(int id)
{
  std::vector<JoinInfo> joinInfos;
  joinInfos.push_back(JoinInfo{ m_SGOMetadata.GetTableName().toStdString(), JoinOperator::LEFT_JOIN });
  PointLightDbInfo pointLight = m_unitOfWork->GetPointLightRepository()->Get(id, &joinInfos);

  return pointLight;
}

QList<PointLightDbInfo> PointLightService::GetAll()
{
  std::vector<JoinInfo> joinInfos;
  joinInfos.push_back(JoinInfo{ m_SGOMetadata.GetTableName().toStdString(), JoinOperator::LEFT_JOIN });
  std::vector<PointLightDbInfo> pointLights = m_unitOfWork->GetPointLightRepository()->GetAll(&joinInfos);

  QList<PointLightDbInfo> qListPointLights;
  qListPointLights.reserve(pointLights.size());

  std::copy(pointLights.begin(), pointLights.end(), std::back_inserter(qListPointLights));

  return qListPointLights;
}

int PointLightService::Create(PointLightDbInfo& pointLight)
{
  int entityId = m_unitOfWork->GetPointLightRepository()->Create(pointLight);
  pointLight.id = entityId;
  return entityId;
}
void PointLightService::Update(PointLightDbInfo& pointLight)
{
  m_unitOfWork->GetPointLightRepository()->Update(pointLight);
}

void PointLightService::Delete(int id)
{
  m_unitOfWork->GetPointLightRepository()->Delete(id);
}

QList<PointLightDbInfo> PointLightService::GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string name, std::string sgoName)
{
  std::vector<std::string> whereParams;
  std::string whereParamsGlue = " AND ";
  parameters.whereCondition = "";
  bool filteringIsEnabled = false;
  std::vector<PointLightDbInfo> gameObjects;
  QList<PointLightDbInfo> qListGameObjects;

 
  if (!name.empty()) {
    whereParams.push_back(" " + m_pointLightMetadata.GetAlias(0).toStdString() + " LIKE '%" + name + "%' ");
    filteringIsEnabled = true;
  }

  if (!sgoName.empty()) {
    whereParams.push_back(" " + m_SGOMetadata.GetAlias(0).toStdString() + " LIKE '%" + sgoName + "%' ");
    filteringIsEnabled = true;
  }

  if (filteringIsEnabled)
    parameters.whereCondition = Utils::Join(whereParams, whereParamsGlue);

  else
    parameters.whereCondition = "1";

  parameters.joinInfos.clear();
  parameters.joinInfos.push_back(JoinInfo{ m_SGOMetadata.GetTableName().toStdString(), JoinOperator::LEFT_JOIN });
  gameObjects = m_unitOfWork->GetPointLightRepository()->GetAll(parameters, pagingInfo);
  qListGameObjects.reserve(gameObjects.size());

  std::copy(gameObjects.begin(), gameObjects.end(), std::back_inserter(qListGameObjects));

  return qListGameObjects;
}

QList<PointLightDbInfo> PointLightService::GetPointLightsBySgoId(int id)
{
  GetParameters parameters;
  PagingInfo pagingInfo;
  parameters.onPage = INT_MAX;
  std::vector<PointLightDbInfo> gameObjects;
  QList<PointLightDbInfo> qListGameObjects;

  parameters.whereCondition = QString("%1 = %2").arg(m_pointLightMetadata.GetAlias(1), QString::number(id)).toStdString();

  parameters.joinInfos.clear();
  parameters.joinInfos.push_back(JoinInfo{ m_SGOMetadata.GetTableName().toStdString(), JoinOperator::LEFT_JOIN });
  gameObjects = m_unitOfWork->GetPointLightRepository()->GetAll(parameters, pagingInfo);
  qListGameObjects.reserve(gameObjects.size());

  std::copy(gameObjects.begin(), gameObjects.end(), std::back_inserter(qListGameObjects));

  return qListGameObjects;
}