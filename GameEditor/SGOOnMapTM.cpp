#include "SGOOnMapTM.h"

SGOOnMapTM::SGOOnMapTM(int onPage, QObject *parent)
  : GETable<SGOOnMapDbInfo>(parent)
{
  m_SGOOnMapService = DependencyResolver::GetSGOOnMapService();
  Initialize(onPage);
}

void SGOOnMapTM::FillOrderFieldMap()
{
  SGOOnMapMetadata metadata;

  m_orderFieldMap.insert(std::pair<int, std::string>(0, metadata.GetSelectInfos()[metadata.GetColumnNames()[0]].aliasColumnName.toStdString()));

  QString SGOTableName = metadata.GetRelationShips().begin()->first;
  m_orderFieldMap.insert(std::pair<int, std::string>(1, metadata.GetRelationShipAlias(SGOTableName, 0).toStdString()));

  for (int i = 1; i < metadata.GetColumnNames().size(); ++i)
    m_orderFieldMap.insert(std::pair<int, std::string>(i + 1, metadata.GetSelectInfos()[metadata.GetColumnNames()[i]].aliasColumnName.toStdString()));
}

void SGOOnMapTM::GetData()
{
  m_data = m_SGOOnMapService->GetFiltered(m_getParameters, m_pagingInfo, m_SGONameFilter, m_instanceNameFilter);
}

bool SGOOnMapTM::setData(const QModelIndex & index, const QVariant & value, int role)
{
  if (role == Qt::CheckStateRole)
  {
    if (index.column() == 9) {
      auto sgo =  m_data.at(index.row());
      if (value.toBool())
        emit FreezeSgoSignal(sgo.id);
      else
        emit UnfreezeSgoSignal(sgo.id);
    }

    this->endResetModel();
  }
  return true;
}

Qt::ItemFlags SGOOnMapTM::flags(const QModelIndex & index) const
{
  Qt::ItemFlags returnValue = Qt::ItemIsSelectable | Qt::ItemIsEnabled;

  if (index.column() == 9)
    returnValue |= Qt::ItemIsUserCheckable | Qt::ItemIsEditable;

  return returnValue;
}

QVariant SGOOnMapTM::data(const QModelIndex &index, int role) const
{
  switch (role) {
    case Qt::TextAlignmentRole:

      if (index.column() >= 3 && index.column() <= 8)
        return Qt::AlignRight;

      break;

    case Qt::CheckStateRole:

      if (index.column() == 9) {
        const auto & sgoOnMap = m_data[index.row()];
        return (sgoOnMap.isFrozen ? Qt::Checked : Qt::Unchecked);
      }
        

      break;

    case Qt::DisplayRole:

      const auto & sgoOnMap = m_data[index.row()];

      switch (index.column())
      {
        case 0: return sgoOnMap.id;
        case 1: return sgoOnMap.staticGameObjectDbInfo.name;
        case 2: return sgoOnMap.instanceName;
        case 3: return sgoOnMap.xPos;
        case 4: return sgoOnMap.yPos;
        case 5: return sgoOnMap.zPos;
        case 6: return sgoOnMap.xRotate;
        case 7: return sgoOnMap.yRotate;
        case 8: return sgoOnMap.zRotate;
        default: return{};
      }

      break;
  }

  return QVariant();
}

QVariant SGOOnMapTM::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return{};
  switch (section) {
    case 0: return "Id";
    case 1: return tr("SGO name");
    case 2: return tr("instance name");
    case 3: return tr("x pos");
    case 4: return tr("y pos");
    case 5: return tr("z pos");
    case 6: return tr("x rotate");
    case 7: return tr("y rotate");
    case 8: return tr("z rotate");
    case 9: return tr("frozen");
    default: return{};
  }
}

SGOOnMapTM::~SGOOnMapTM()
{
}

void SGOOnMapTM::appendEntity(SGOOnMapDbInfo& gameObject)
{
  m_SGOOnMapService->Create(gameObject);
  emit SGOCountChanged(gameObject.staticGameObjectId);
}

void SGOOnMapTM::editEntity(SGOOnMapDbInfo& gameObject)
{
  m_SGOOnMapService->Update(gameObject);
}

void SGOOnMapTM::removeEntity(int id)
{
  auto sgo = m_SGOOnMapService->Get(id);
  int staticGameObjectId = sgo.staticGameObjectId;
  m_SGOOnMapService->Delete(id);
  emit SGOCountChanged(staticGameObjectId);
}

bool SGOOnMapTM::ContainsInMemory(int id)
{
  auto findIterator = std::find_if(m_data.begin(), m_data.end(), [=](const SGOOnMapDbInfo& sgo) -> bool { return sgo.id == id; });
  return findIterator != m_data.end();
}

void SGOOnMapTM::UpdateTable(int pageNumber, int onPage, int orderFieldIndex, Qt::SortOrder orderDirection, QString SGONameFilter, QString instanceNameFilter)
{
  m_getParameters.pageNumber = pageNumber;
  m_getParameters.onPage = onPage;
  m_getParameters.orderFieldName = m_orderFieldMap[orderFieldIndex];
  m_getParameters.orderDirection = orderDirection == Qt::SortOrder::AscendingOrder ? OrderDirection::ASC : OrderDirection::DESC;

  m_SGONameFilter = SGONameFilter.toStdString();
  m_instanceNameFilter = instanceNameFilter.toStdString();
  UpdateData();
}

SGOOnMapDbInfo SGOOnMapTM::GetEntityByKey(int id)
{
  return m_SGOOnMapService->Get(id);
}

void SGOOnMapTM::EditPosition(int id, float x, float y, float z)
{
  m_SGOOnMapService->SetPosition(id, x, y, z);
  if (ContainsInMemory(id))
    UpdateData();
}

void SGOOnMapTM::EditRotation(int id, float x, float y, float z)
{
  m_SGOOnMapService->SetRotation(id, x, y, z);
  if (ContainsInMemory(id))
    UpdateData();
}