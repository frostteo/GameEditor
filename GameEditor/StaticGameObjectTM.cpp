#include "StaticGameObjectTM.h"


StaticGameObjectTM::StaticGameObjectTM(int onPage, QObject * parent) : QAbstractTableModel{ parent }
{
  m_staticGOService = DependencyResolver::GetStaticGOService();
  m_getParameters.onPage = onPage;
  m_SGOTableOrderFieldMap.insert(std::pair<int, std::string>(0, "id"));
  m_SGOTableOrderFieldMap.insert(std::pair<int, std::string>(1, "name"));
  m_SGOTableOrderFieldMap.insert(std::pair<int, std::string>(2, "modelFileName"));
  UpdateData();
}


StaticGameObjectTM::~StaticGameObjectTM()
{
}

void StaticGameObjectTM::UpdateData()
{
  this->beginResetModel();
  m_data = m_staticGOService->GetFiltered(m_getParameters, m_pagingInfo, m_SGONameFilter, m_modelFileNameFilter);
  this->endResetModel();
  emit TableDataChanged();
  emit PagingInfoChanged(m_pagingInfo);
}

void StaticGameObjectTM::UpdateTable(int pageNumber, int onPage, int orderFieldIndex, Qt::SortOrder orderDirection, QString SGONameFilter, QString SGOModelFilenameFilter)
{
  m_getParameters.pageNumber = pageNumber;
  m_getParameters.onPage = onPage;
  m_getParameters.orderFieldName = m_SGOTableOrderFieldMap[orderFieldIndex];
  m_getParameters.orderDirection = orderDirection == Qt::SortOrder::AscendingOrder ? OrderDirection::ASC : OrderDirection::DESC;

  m_SGONameFilter = SGONameFilter.toStdString();
  m_modelFileNameFilter = SGOModelFilenameFilter.toStdString();
  UpdateData();
}

QVariant StaticGameObjectTM::data(const QModelIndex &index, int role) const
{
  if (role != Qt::DisplayRole && role != Qt::EditRole) return{};
  const auto & gameObject = m_data[index.row()];

  switch (index.column())
  {
    case 0: return gameObject.id;
    case 1: return gameObject.name;
    case 2: return gameObject.modelFileName;
    default: return{};
  }
}

QVariant StaticGameObjectTM::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return{};
  switch (section) {
    case 0: return "Id";
    case 1: return tr("Name");
    case 2: return tr("Model filename");
    default: return{};
  }
}

void StaticGameObjectTM::append(StaticGameObjectDbInfo& gameObject)
{
  beginInsertRows({}, m_data.count(), m_data.count());
  m_staticGOService->CreateStaticGameObject(gameObject);
  UpdateData();
  endInsertRows();
}

void StaticGameObjectTM::edit(StaticGameObjectDbInfo& gameObject)
{
  m_staticGOService->UpdateStaticGameObject(gameObject);
  UpdateData();
}

void StaticGameObjectTM::remove(int id)
{
  m_staticGOService->DeleteStaticGameObject(id);
  UpdateData();
}

StaticGameObjectDbInfo StaticGameObjectTM::GetStaticGameObject(int rowNumber)
{
  return m_data.at(rowNumber);
}