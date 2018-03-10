#include "PointLightMetadata.h"
#include "Logger.h"

PointLightMetadata::PointLightMetadata()
{
  m_tableName = "PointLight";
  m_columnNames = { "name", "sgoId", "relativePosX", "relativePosY", "relativePosZ", "red", "green", "blue", "linearAttenuation", "quadraticAttenuation", "castShadows", "countOnMap"};
  AddRelationShip(m_SGOMetadata.GetTableName(), m_columnNames[1], m_SGOMetadata.GetKeyColumnName());
}


PointLightMetadata::~PointLightMetadata()
{
}

void PointLightMetadata::InitializeFromQuery(PointLightDbInfo& entity, QSqlQuery* query, std::vector<QString>* joinTableNames)
{
  auto selectInfos = GetSelectInfos();

  entity.id = query->value(selectInfos[GetKeyColumnName()].aliasColumnName).toInt();
  entity.name = query->value(selectInfos[m_columnNames[0]].aliasColumnName).toString();
  entity.staticGameObjectId = query->value(selectInfos[m_columnNames[1]].aliasColumnName).toInt();
  entity.relativePosX = query->value(selectInfos[m_columnNames[2]].aliasColumnName).toFloat();
  entity.relativePosY = query->value(selectInfos[m_columnNames[3]].aliasColumnName).toFloat();
  entity.relativePosZ = query->value(selectInfos[m_columnNames[4]].aliasColumnName).toFloat();
  entity.red = query->value(selectInfos[m_columnNames[5]].aliasColumnName).toFloat();
  entity.green = query->value(selectInfos[m_columnNames[6]].aliasColumnName).toFloat();
  entity.blue = query->value(selectInfos[m_columnNames[7]].aliasColumnName).toFloat();
  entity.linearAttenuation = query->value(selectInfos[m_columnNames[8]].aliasColumnName).toFloat();
  entity.quadraticAttenuation = query->value(selectInfos[m_columnNames[9]].aliasColumnName).toFloat();
  entity.castShadows = query->value(selectInfos[m_columnNames[10]].aliasColumnName).toBool();
  entity.countOnMap = query->value(selectInfos[m_columnNames[11]].aliasColumnName).toInt();

  if (joinTableNames != nullptr && joinTableNames->size() > 0) {
    if (std::find(joinTableNames->begin(), joinTableNames->end(), m_relationships.begin()->first) != joinTableNames->end())
      m_SGOMetadata.InitializeFromQuery(entity.staticGameObjectDbInfo, query, joinTableNames);

  }
}

QVariant PointLightMetadata::GetFieldByName(const PointLightDbInfo& entity, QString name)
{
  if (name == m_columnNames[0])
    return entity.name;

  if (name == m_columnNames[1])
  {
    if (entity.staticGameObjectId == 0)
      return QVariant();

    return entity.staticGameObjectId;
  }

  if (name == m_columnNames[2])
    return entity.relativePosX;

  if (name == m_columnNames[3])
    return entity.relativePosY;

  if (name == m_columnNames[4])
    return entity.relativePosZ;

  if (name == m_columnNames[5])
    return entity.red;

  if (name == m_columnNames[6])
    return entity.green;

  if (name == m_columnNames[7])
    return entity.blue;

  if (name == m_columnNames[8])
    return entity.linearAttenuation;

  if (name == m_columnNames[9])
    return entity.quadraticAttenuation;

  if (name == m_columnNames[10])
    return entity.castShadows;

  if (name == m_columnNames[11])
    return entity.countOnMap;

  if (name == GetKeyColumnName())
    return entity.id;

  RUNTIME_ERROR(("There is no field with name = " + name + " in entity").toStdString());
}

QString PointLightMetadata::GetSelectColumnString(std::vector<QString>* joinTableNames)
{
  if (m_selectColumnsStr.isEmpty())
    BuildSelectColumnsStr();

  if (joinTableNames == nullptr || joinTableNames->size() == 0)
    return m_selectColumnsStr;

  if (std::find(joinTableNames->begin(), joinTableNames->end(), m_relationships.begin()->first) != joinTableNames->end())
    return m_selectColumnsStr + COMA + m_SGOMetadata.GetSelectColumnString();

  RUNTIME_ERROR("Incorrect table for relationship");
}

QString PointLightMetadata::GetRelationShipAlias(QString tableName, int columnIndex)
{
  if (tableName == m_relationships.begin()->first)
  {
    return m_SGOMetadata.GetAlias(columnIndex);
  }

  RUNTIME_ERROR("there is no relationship with such name: " + tableName.toStdString())
}

QString PointLightMetadata::GetDefaultOrderString()
{
  return GetAlias(1);
}