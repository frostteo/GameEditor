#include "SGOOnMapMetadata.h"


SGOOnMapMetadata::SGOOnMapMetadata()
{
  m_tableName = "SGOOnMapDbInfo";
  m_columnNames = { "staticGameObjectId", "instanceName" };
  AddRelationShip(m_SGOMetadata.GetTableName(), m_columnNames[0], m_SGOMetadata.GetKeyColumnName());
}


SGOOnMapMetadata::~SGOOnMapMetadata()
{
}

void SGOOnMapMetadata::InitializeFromQuery(SGOOnMapDbInfo& entity, QSqlQuery* query, std::vector<QString>* joinTableNames)
{
  auto selectInfos = GetSelectInfos();

  entity.id = query->value(selectInfos[GetKeyColumnName()].aliasColumnName).toInt();
  entity.staticGameObjectId = query->value(selectInfos[m_columnNames[0]].aliasColumnName).toInt();
  entity.instanceName = query->value(selectInfos[m_columnNames[1]].aliasColumnName).toString();

  if (joinTableNames != nullptr && joinTableNames->size() > 0) {
    if (std::find(joinTableNames->begin(), joinTableNames->end(), m_relationships.begin()->first) != joinTableNames->end())
      m_SGOMetadata.InitializeFromQuery(entity.staticGameObjectDbInfo, query, joinTableNames);
    
  }
}

QVariant SGOOnMapMetadata::GetFieldByName(const SGOOnMapDbInfo& entity, QString name)
{
  if (name == m_columnNames[0])
    return entity.staticGameObjectId;
  
  if (name == m_columnNames[1])
    return entity.instanceName;
  
  if (name == GetKeyColumnName())
    return entity.id;
  
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(("There is no field with name = " + name + " in entity").toStdString(), __FILE__, __LINE__));
}

QString SGOOnMapMetadata::GetSelectColumnString(std::vector<QString>* joinTableNames)
{
  if (m_selectColumnsStr.isEmpty())
    BuildSelectColumnsStr();

  if (joinTableNames == nullptr || joinTableNames->size() == 0)
    return m_selectColumnsStr;
  
  if (std::find(joinTableNames->begin(), joinTableNames->end(), m_relationships.begin()->first) != joinTableNames->end())
    return m_selectColumnsStr + COMA + m_SGOMetadata.GetSelectColumnString();

  throw std::runtime_error(Logger::get().GetErrorTraceMessage("Incorrect table for relationship", __FILE__, __LINE__));
}