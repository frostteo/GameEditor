#include "SGOOnMapRepository.h"

SGOOnMapRepository::SGOOnMapRepository()
{
}


SGOOnMapRepository::~SGOOnMapRepository()
{
}

IRepository<SGOOnMapDbInfo>* SGOOnMapRepository::Initialize(std::string connectionName)
{
  m_tableMetadata = std::unique_ptr<SGOOnMapMetadata>(new SGOOnMapMetadata());
  m_defaultOrderField = m_tableMetadata->GetDefaultOrderString();

  QtRepository<SGOOnMapDbInfo>::Initialize(connectionName);
  QSqlQuery query(GetDatabase());

  query.prepare(QString("CREATE TABLE IF NOT EXISTS %1 (%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 INTEGER , %4 TEXT UNIQUE, FOREIGN KEY(%3) REFERENCES %5(%6) ON DELETE CASCADE ON UPDATE CASCADE)").
    arg(m_tableMetadata->GetTableName(), m_tableMetadata->GetKeyColumnName(), m_tableMetadata->GetColumnNames()[0], m_tableMetadata->GetColumnNames()[1], m_tableMetadata->GetRelationShips().begin()->first, m_tableMetadata->GetRelationShips().begin()->second.OtherTablePrimaryKeyName));

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(query.lastError().text().toStdString(), __FILE__, __LINE__));

  return this;
}

