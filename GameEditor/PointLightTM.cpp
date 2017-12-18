#include "PointLightTM.h"

PointLightTM::PointLightTM(int onPage, QObject * parent) : GETable<PointLightDbInfo>(parent)
{
  m_pointLightService = DependencyResolver::GetPointLightService();
  Initialize(onPage);
}

void PointLightTM::FillOrderFieldMap()
{
  PointLightMetadata metadata;
  m_orderFieldMap.insert(std::pair<int, std::string>(0, metadata.GetSelectInfos()[metadata.GetKeyColumnName()].aliasColumnName.toStdString()));
  m_orderFieldMap.insert(std::pair<int, std::string>(1, metadata.GetAlias(0).toStdString()));

  QString SGOTableName = metadata.GetRelationShips().begin()->first;
  m_orderFieldMap.insert(std::pair<int, std::string>(2, metadata.GetRelationShipAlias(SGOTableName, 0).toStdString()));

  for (int i = 2; i < metadata.GetColumnNames().size(); ++i)
    m_orderFieldMap.insert(std::pair<int, std::string>(i + 1, metadata.GetAlias(i).toStdString()));
}

PointLightTM::~PointLightTM()
{
}

void PointLightTM::GetData()
{
  m_data = m_pointLightService->GetFiltered(m_getParameters, m_pagingInfo, m_nameFilter, m_sgoNameFilter);
}

void PointLightTM::UpdateTable(int pageNumber, int onPage, int orderFieldIndex, Qt::SortOrder orderDirection, QString nameFilter, QString SGONameFilter)
{
  m_getParameters.pageNumber = pageNumber;
  m_getParameters.onPage = onPage;
  m_getParameters.orderFieldName = m_orderFieldMap[orderFieldIndex];
  m_getParameters.orderDirection = orderDirection == Qt::SortOrder::AscendingOrder ? OrderDirection::ASC : OrderDirection::DESC;

  m_nameFilter = nameFilter.toStdString();
  m_sgoNameFilter = SGONameFilter.toStdString();
  UpdateData();
}

QVariant PointLightTM::data(const QModelIndex &index, int role) const
{
  switch (role)
  {
  case Qt::TextAlignmentRole:

    if (index.column() == 0 || index.column() >= 3 && index.column() <= 8)
      return Qt::AlignVCenter | Qt::AlignRight;

    break;

  case Qt::DisplayRole:

    const auto & pointLight = m_data[index.row()];
    switch (index.column())
    {
      case 0: return pointLight.id;
      case 1: return pointLight.name;
      case 2: return pointLight.staticGameObjectDbInfo.name;
      case 3: return pointLight.relativePosX;
      case 4: return pointLight.relativePosY;
      case 5: return pointLight.relativePosZ;
      case 6: return pointLight.red;
      case 7: return pointLight.green;
      case 8: return pointLight.blue;
      case 9: return pointLight.linearAttenuation;
      case 10: return pointLight.quadraticAttenuation;
      case 11: return pointLight.countOnMap;
      default: return{};
    }

    break;
  }

  return QVariant();
}

QVariant PointLightTM::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation != Qt::Horizontal || role != Qt::DisplayRole) 
    return{};

  switch (section) {
    case 0: return "Id";
    case 1: return tr("Name");
    case 2: return tr("sgo name");
    case 3: return tr("relative pos x");
    case 4: return tr("relative pos y");
    case 5: return tr("relative pos z");
    case 6: return tr("red");
    case 7: return tr("green");
    case 8: return tr("blue");
    case 9: return tr("linnear attenuation");
    case 10: return tr("quadratic attenuation");
    case 11: return tr("count of map");
    default: return{};
  }
}

void PointLightTM::appendEntity(PointLightDbInfo& pointLight)
{
  m_pointLightService->Create(pointLight);
}

void PointLightTM::editEntity(PointLightDbInfo& pointLight)
{
  m_pointLightService->Update(pointLight);
}

void PointLightTM::removeEntity(int id)
{
  m_pointLightService->Delete(id);
}

bool PointLightTM::ContainsInMemory(int id)
{
  auto findIterator = std::find_if(m_data.begin(), m_data.end(), [=](const PointLightDbInfo& pointLight) -> bool { return pointLight.id == id; });
  return findIterator != m_data.end();
}

PointLightDbInfo PointLightTM::GetEntityByKey(int id)
{
  return m_pointLightService->Get(id);
}