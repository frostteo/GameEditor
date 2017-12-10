#include "PointLightOnMapMetadata.h"


PointLightOnMapMetadata::PointLightOnMapMetadata()
{
  m_tableName = "PointLightOnMap";
  m_columnNames = { "pointLightId", "instanceName", "xPox", "yPos", "zPos", "xRotate", "yRotate", "zRotate", "linearAttenuation", "quadraticAttenuation", "isFrozen" };
  AddRelationShip(m_pointLightMetadata.GetTableName(), m_columnNames[0], m_pointLightMetadata.GetKeyColumnName());
}

void PointLightOnMapMetadata::BuildJoinConditions()
{
  DbTableMetadata<PointLightOnMapDbInfo>::BuildJoinConditions();
  auto pointLightJoinCondition = m_pointLightMetadata.GetJoinConditions();
  m_joinConditions.insert(pointLightJoinCondition.begin(), pointLightJoinCondition.end());
}

PointLightOnMapMetadata::~PointLightOnMapMetadata()
{
}

void PointLightOnMapMetadata::InitializeFromQuery(PointLightOnMapDbInfo& entity, QSqlQuery* query, std::vector<QString>* joinTableNames)
{
  auto selectInfos = GetSelectInfos();

  entity.id = query->value(selectInfos[GetKeyColumnName()].aliasColumnName).toInt();
  entity.pointLightId = query->value(selectInfos[m_columnNames[0]].aliasColumnName).toInt();
  entity.instanceName = query->value(selectInfos[m_columnNames[1]].aliasColumnName).toString();
  entity.xPos = query->value(selectInfos[m_columnNames[2]].aliasColumnName).toFloat();
  entity.yPos = query->value(selectInfos[m_columnNames[3]].aliasColumnName).toFloat();
  entity.zPos = query->value(selectInfos[m_columnNames[4]].aliasColumnName).toFloat();
  entity.xRotate = query->value(selectInfos[m_columnNames[5]].aliasColumnName).toFloat();
  entity.yRotate = query->value(selectInfos[m_columnNames[6]].aliasColumnName).toFloat();
  entity.zRotate = query->value(selectInfos[m_columnNames[7]].aliasColumnName).toFloat();
  entity.linearAttenuation = query->value(selectInfos[m_columnNames[8]].aliasColumnName).toFloat();
  entity.quadraticAttenuation = query->value(selectInfos[m_columnNames[9]].aliasColumnName).toFloat();
  entity.isFrozen = query->value(selectInfos[m_columnNames[10]].aliasColumnName).toInt() == 1;

  if (joinTableNames != nullptr && joinTableNames->size() > 0) {
    if (std::find(joinTableNames->begin(), joinTableNames->end(), m_relationships.begin()->first) != joinTableNames->end())
      m_pointLightMetadata.InitializeFromQuery(entity.pointLightDbInfo, query, joinTableNames);

  }
}

QVariant PointLightOnMapMetadata::GetFieldByName(const PointLightOnMapDbInfo& entity, QString name)
{
  if (name == m_columnNames[0])
    return entity.pointLightId;

  if (name == m_columnNames[1])
    return entity.instanceName;

  if (name == m_columnNames[2])
    return entity.xPos;

  if (name == m_columnNames[3])
    return entity.yPos;

  if (name == m_columnNames[4])
    return entity.zPos;

  if (name == m_columnNames[5])
    return entity.xRotate;

  if (name == m_columnNames[6])
    return entity.yRotate;

  if (name == m_columnNames[7])
    return entity.zRotate;

  if (name == m_columnNames[8])
    return entity.linearAttenuation;

  if (name == m_columnNames[9])
    return entity.quadraticAttenuation;

  if (name == m_columnNames[10])
    return entity.isFrozen? 1 : 0;

  if (name == GetKeyColumnName())
    return entity.id;

  throw std::runtime_error(Logger::get().GetErrorTraceMessage(("There is no field with name = " + name + " in entity").toStdString(), __FILE__, __LINE__));
}

QString PointLightOnMapMetadata::GetSelectColumnString(std::vector<QString>* joinTableNames)
{
  if (m_selectColumnsStr.isEmpty())
    BuildSelectColumnsStr();

  if (joinTableNames == nullptr || joinTableNames->size() == 0)
    return m_selectColumnsStr;

  if (std::find(joinTableNames->begin(), joinTableNames->end(), m_pointLightMetadata.GetTableName()) != joinTableNames->end())
    m_selectColumnsStr = m_selectColumnsStr + COMA + m_pointLightMetadata.GetSelectColumnString();

  if (std::find(joinTableNames->begin(), joinTableNames->end(), m_sgoMetadata.GetTableName()) != joinTableNames->end())
    m_selectColumnsStr = m_selectColumnsStr + COMA + m_sgoMetadata.GetSelectColumnString();

  return m_selectColumnsStr;
  throw std::runtime_error(Logger::get().GetErrorTraceMessage("Incorrect table for relationship", __FILE__, __LINE__));
}

QString PointLightOnMapMetadata::GetRelationShipAlias(QString tableName, int columnIndex)
{
  if (tableName == m_relationships.begin()->first)
  {
    return m_pointLightMetadata.GetAlias(columnIndex);
  }

  RUNTIME_ERROR("there is no relationship with such name: " + tableName.toStdString())
}
