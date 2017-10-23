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

  QString createTableString = QString("CREATE TABLE IF NOT EXISTS %1 (%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 INTEGER , %4 TEXT UNIQUE, %5 REAL, %6 REAL, %7 REAL, %8 REAL, %9 REAL, ").arg(m_tableMetadata->GetTableName(), m_tableMetadata->GetKeyColumnName(), m_tableMetadata->GetColumnNames()[0], m_tableMetadata->GetColumnNames()[1], m_tableMetadata->GetColumnNames()[2], m_tableMetadata->GetColumnNames()[3], m_tableMetadata->GetColumnNames()[4], m_tableMetadata->GetColumnNames()[5], m_tableMetadata->GetColumnNames()[6]);

  createTableString = QString("%1 %2 REAL, FOREIGN KEY(%3) REFERENCES %4(%5) ON DELETE CASCADE ON UPDATE CASCADE)").arg(createTableString, m_tableMetadata->GetColumnNames()[7], m_tableMetadata->GetColumnNames()[0], m_tableMetadata->GetRelationShips().begin()->first, m_tableMetadata->GetRelationShips().begin()->second.OtherTablePrimaryKeyName);

  query.prepare(createTableString);

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(query.lastError().text().toStdString(), __FILE__, __LINE__));

  return this;
}

