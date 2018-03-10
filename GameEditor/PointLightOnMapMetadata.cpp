#include "PointLightOnMapMetadata.h"

PointLightOnMapMetadata::PointLightOnMapMetadata()
{
  m_tableName = "PointLightOnMap";
  m_columnNames = { "pointLightId", "sgoOnMapId", "red", "green", "blue", "linearAttenuation", "quadraticAttenuation", "castShadows", "shadowDirections" };
  AddRelationShip(m_pointLightMetadata.GetTableName(), m_columnNames[0], m_pointLightMetadata.GetKeyColumnName());
  AddRelationShip(m_SGOOnMapMetadata.GetTableName(), m_columnNames[1], m_SGOOnMapMetadata.GetKeyColumnName());
}

void PointLightOnMapMetadata::BuildJoinConditions()
{
  DbTableMetadata<PointLightOnMapDbInfo>::BuildJoinConditions();
  auto sgoOnMapJoinCondition = m_SGOOnMapMetadata.GetJoinConditions();
  m_joinConditions.insert(sgoOnMapJoinCondition.begin(), sgoOnMapJoinCondition.end());
}

PointLightOnMapMetadata::~PointLightOnMapMetadata()
{
}

void PointLightOnMapMetadata::InitializeFromQuery(PointLightOnMapDbInfo& entity, QSqlQuery* query, std::vector<QString>* joinTableNames)
{
  auto selectInfos = GetSelectInfos();

  entity.id = query->value(selectInfos[GetKeyColumnName()].aliasColumnName).toInt();
  entity.pointLightId = query->value(selectInfos[m_columnNames[0]].aliasColumnName).toInt();
  entity.sgoOnMapId = query->value(selectInfos[m_columnNames[1]].aliasColumnName).toInt();
  entity.red = query->value(selectInfos[m_columnNames[2]].aliasColumnName).toFloat();
  entity.green = query->value(selectInfos[m_columnNames[3]].aliasColumnName).toFloat();
  entity.blue = query->value(selectInfos[m_columnNames[4]].aliasColumnName).toFloat();
  entity.linearAttenuation = query->value(selectInfos[m_columnNames[5]].aliasColumnName).toFloat();
  entity.quadraticAttenuation = query->value(selectInfos[m_columnNames[6]].aliasColumnName).toFloat();
  entity.castShadows = query->value(selectInfos[m_columnNames[7]].aliasColumnName).toBool();
  entity.shadowDirections = query->value(selectInfos[m_columnNames[8]].aliasColumnName).toInt();

  if (joinTableNames != nullptr && joinTableNames->size() > 0) {
    if (std::find(joinTableNames->begin(), joinTableNames->end(), m_pointLightMetadata.GetTableName()) != joinTableNames->end())
      m_pointLightMetadata.InitializeFromQuery(entity.pointLightDbInfo, query, joinTableNames);

    if (std::find(joinTableNames->begin(), joinTableNames->end(), m_SGOOnMapMetadata.GetTableName()) != joinTableNames->end())
      m_SGOOnMapMetadata.InitializeFromQuery(entity.sgoOnMapDbInfo, query, joinTableNames);
  }
}

QVariant PointLightOnMapMetadata::GetFieldByName(const PointLightOnMapDbInfo& entity, QString name)
{
  if (name == m_columnNames[0])
    return entity.pointLightId;

  if (name == m_columnNames[1])
    return entity.sgoOnMapId;

  if (name == m_columnNames[2])
    return entity.red;

  if (name == m_columnNames[3])
    return entity.green;

  if (name == m_columnNames[4])
    return entity.blue;

  if (name == m_columnNames[5])
    return entity.linearAttenuation;

  if (name == m_columnNames[6])
    return entity.quadraticAttenuation;

  if (name == m_columnNames[7])
    return entity.castShadows;

  if (name == m_columnNames[8])
    return entity.shadowDirections;

  if (name == GetKeyColumnName())
    return entity.id;

  RUNTIME_ERROR(("There is no field with name = " + name + " in entity").toStdString());
}

QString PointLightOnMapMetadata::GetSelectColumnString(std::vector<QString>* joinTableNames)
{
  QString selectColumnsStr;

  if (m_selectColumnsStr.isEmpty())
    BuildSelectColumnsStr();
  
  if (joinTableNames == nullptr || joinTableNames->size() == 0)
    return m_selectColumnsStr;

  selectColumnsStr = m_selectColumnsStr;

  if (std::find(joinTableNames->begin(), joinTableNames->end(), m_pointLightMetadata.GetTableName()) != joinTableNames->end())
    selectColumnsStr += COMA + m_pointLightMetadata.GetSelectColumnString();

  if (std::find(joinTableNames->begin(), joinTableNames->end(), m_sgoMetadata.GetTableName()) != joinTableNames->end())
    selectColumnsStr += COMA + m_sgoMetadata.GetSelectColumnString();

  if (std::find(joinTableNames->begin(), joinTableNames->end(), m_SGOOnMapMetadata.GetTableName()) != joinTableNames->end())
    selectColumnsStr += COMA + m_SGOOnMapMetadata.GetSelectColumnString();

  return selectColumnsStr;
}

QString PointLightOnMapMetadata::GetRelationShipAlias(QString tableName, int columnIndex)
{
  if (tableName == m_pointLightMetadata.GetTableName())
    return m_pointLightMetadata.GetAlias(columnIndex);

  if (tableName == m_sgoMetadata.GetTableName())
    return m_sgoMetadata.GetAlias(columnIndex);

  if (tableName == m_SGOOnMapMetadata.GetTableName())
    return m_SGOOnMapMetadata.GetAlias(columnIndex);

  RUNTIME_ERROR("there is no relationship with such name: " + tableName.toStdString())
}
