#include "SGOMetadata.h"


SGOMetadata::SGOMetadata()
{
  m_tableName = "StaticGameObject";
  m_columnNames = { "name", "modelFileName", "countOnMap", "isService" };
}


SGOMetadata::~SGOMetadata()
{
}

void SGOMetadata::InitializeFromQuery(StaticGameObjectDbInfo& entity, QSqlQuery* query, std::vector<QString>* joinTableNames)
{
  auto selectInfos = GetSelectInfos();

  entity.id = query->value(selectInfos[GetKeyColumnName()].aliasColumnName).toInt();
  entity.name = query->value(selectInfos[m_columnNames[0]].aliasColumnName).toString();
  entity.modelFileName = query->value(selectInfos[m_columnNames[1]].aliasColumnName).toString();
  entity.countOnMap = query->value(selectInfos[m_columnNames[2]].aliasColumnName).toInt();
  entity.isService = query->value(selectInfos[m_columnNames[3]].aliasColumnName).toBool();
}

QVariant SGOMetadata::GetFieldByName(const StaticGameObjectDbInfo& entity, QString name)
{
  if (name == m_columnNames[0])
    return entity.name;

  if (name == m_columnNames[1])
    return entity.modelFileName;

  if (name == m_columnNames[2])
    return entity.countOnMap;

  if (name == m_columnNames[3])
    return entity.isService;

  if (name == GetKeyColumnName())
    return entity.id;

  RUNTIME_ERROR(("There is no field with name = " + name + " in entity").toStdString());
}