#include "StaticGORepository.h"

StaticGORepository::StaticGORepository()
{
}

IRepository<StaticGameObjectDbInfo>* StaticGORepository::Initialize(std::string connectionName)
{
  m_tableMetadata = std::unique_ptr<SGOMetadata>(new SGOMetadata());
  m_defaultOrderField = m_tableMetadata->GetDefaultOrderString();

  QtRepository<StaticGameObjectDbInfo>::Initialize(connectionName);

  QSqlQuery query(GetDatabase());

  query.prepare(QString("CREATE TABLE IF NOT EXISTS %1 (%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 TEXT UNIQUE, %4 TEXT, %5 INTEGER, %6 INTEGER NOT NULL)").
    arg(m_tableMetadata->GetTableName(), m_tableMetadata->GetKeyColumnName(), m_tableMetadata->GetColumnNames()[0], m_tableMetadata->GetColumnNames()[1], m_tableMetadata->GetColumnNames()[2], m_tableMetadata->GetColumnNames()[3]));

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(query.lastError().text().toStdString(), __FILE__, __LINE__));
  
  return this;
}