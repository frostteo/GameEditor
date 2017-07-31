#include "StaticGameObjectTM.h"


StaticGameObjectTM::StaticGameObjectTM(QObject * parent) : QAbstractTableModel{ parent }
{
  m_staticGOService = DependencyResolver::GetStaticGOService();
  UpdateData();
}


StaticGameObjectTM::~StaticGameObjectTM()
{
}

void StaticGameObjectTM::UpdateData()
{
  m_data = m_staticGOService->GetStaticGameObjects();
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
    case 3: return gameObject.materialFileName;
    default: return{};
  }
}

QVariant StaticGameObjectTM::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return{};
  switch (section) {
    case 0: return "Id";
    case 1: return QtUtils::ToRussian("Имя");
    case 2: return QtUtils::ToRussian("Файл модели");
    case 3: return QtUtils::ToRussian("Файл материала");
    default: return{};
  }
}

void StaticGameObjectTM::append(const StaticGameObject& gameObject)
{
  beginInsertRows({}, m_data.count(), m_data.count());
  m_staticGOService->CreateStaticGameObject(gameObject);
  UpdateData();
  endInsertRows();
}