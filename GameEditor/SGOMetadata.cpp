#include "SGOMetadata.h"


SGOMetadata::SGOMetadata()
{
  m_tableName = "StaticGameObjectDbInfo";
  m_columnNames = { "name", "modelFileName" };
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
}

QVariant SGOMetadata::GetFieldByName(const StaticGameObjectDbInfo& entity, QString name)
{
  if (name == m_columnNames[0])
    return entity.name;

  if (name == m_columnNames[1])
    return entity.modelFileName;

  if (name == GetKeyColumnName())
    return entity.id;

  throw std::runtime_error(Logger::get().GetErrorTraceMessage(("There is no field with name = " + name + " in entity").toStdString(), __FILE__, __LINE__));
}