#include "StaticGameObjectTM.h"


StaticGameObjectTM::StaticGameObjectTM(int onPage, QObject * parent)
  : GETable<StaticGameObjectDbInfo>(parent),
  m_staticGOService(DependencyResolver::GetStaticGOService())
{
  Initialize(onPage);
}

void StaticGameObjectTM::FillOrderFieldMap()
{
  SGOMetadata metadata;
  m_orderFieldMap.insert(std::pair<int, std::string>(0, metadata.GetKeyColumnName().toStdString()));

  for (int i = 0; i < metadata.GetColumnNames().size(); ++i)
    m_orderFieldMap.insert(std::pair<int, std::string>(i + 1, metadata.GetAlias(i).toStdString()));
}

StaticGameObjectTM::~StaticGameObjectTM()
{
}

void StaticGameObjectTM::GetData()
{
  m_data = m_staticGOService->GetFilteredWithoutService(m_getParameters, m_pagingInfo, m_SGONameFilter, m_modelFileNameFilter);
}

void StaticGameObjectTM::UpdateTable(int pageNumber, int onPage, int orderFieldIndex, Qt::SortOrder orderDirection, QString SGONameFilter, QString SGOModelFilenameFilter)
{
  m_getParameters.pageNumber = pageNumber;
  m_getParameters.onPage = onPage;
  m_getParameters.orderFieldName = m_orderFieldMap[orderFieldIndex];
  m_getParameters.orderDirection = orderDirection == Qt::SortOrder::AscendingOrder ? OrderDirection::ASC : OrderDirection::DESC;

  m_SGONameFilter = SGONameFilter.toStdString();
  m_modelFileNameFilter = SGOModelFilenameFilter.toStdString();
  UpdateData();
}

QVariant StaticGameObjectTM::data(const QModelIndex &index, int role) const
{
  switch (role) {
    case Qt::TextAlignmentRole:

      if (index.column() == 0 || index.column() == 3)
        return Qt::AlignRight | Qt::AlignVCenter;

      break;
    case Qt::DisplayRole:

      const auto & gameObject = m_data[index.row()];

      switch (index.column())
      {
        case 0: return gameObject.id;
        case 1: return gameObject.name;
        case 2: return gameObject.modelFileName;
        case 3: return gameObject.countOnMap;
        default: return{};
      }
      break;
  }

  return QVariant();
}

QVariant StaticGameObjectTM::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return{};
  switch (section) {
    case 0: return "Id";
    case 1: return tr("Name");
    case 2: return tr("Model filename");
    case 3: return tr("Count");
    default: return{};
  }
}

void StaticGameObjectTM::appendEntity(StaticGameObjectDbInfo& gameObject)
{
  m_staticGOService->CreateStaticGameObject(gameObject);
}

void StaticGameObjectTM::editEntity(StaticGameObjectDbInfo& gameObject)
{
  m_staticGOService->UpdateStaticGameObject(gameObject);
}

void StaticGameObjectTM::removeEntity(int id)
{
  m_staticGOService->DeleteStaticGameObject(id);
}

bool StaticGameObjectTM::ContainsInMemory(int id)
{
  auto findIterator = std::find_if(m_data.begin(), m_data.end(), [=](const StaticGameObjectDbInfo& sgo) -> bool { return sgo.id == id; });
  return findIterator != m_data.end();
}

StaticGameObjectDbInfo StaticGameObjectTM::GetEntityByKey(int id)
{
  return m_staticGOService->GetStaticGameObject(id);
}