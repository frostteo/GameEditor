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

  QString createTableString = QString("CREATE TABLE IF NOT EXISTS %1 (%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 INTEGER NOT NULL, %4 TEXT, %5 REAL NOT NULL, %6 REAL NOT NULL, %7 REAL NOT NULL, %8 REAL NOT NULL, %9 REAL NOT NULL, ").arg(m_tableMetadata->GetTableName(), m_tableMetadata->GetKeyColumnName(), m_tableMetadata->GetColumnNames()[0], m_tableMetadata->GetColumnNames()[1], m_tableMetadata->GetColumnNames()[2], m_tableMetadata->GetColumnNames()[3], m_tableMetadata->GetColumnNames()[4], m_tableMetadata->GetColumnNames()[5], m_tableMetadata->GetColumnNames()[6]);

  createTableString = QString("%1 %2 REAL NOT NULL, %3 INTEGER NOT NULL, %4 INTEGER NOT NULL DEFAULT(1), %5 INTEGER NOT NULL, FOREIGN KEY(%6) REFERENCES %7(%8) ON DELETE CASCADE ON UPDATE CASCADE)").arg(createTableString, m_tableMetadata->GetColumnNames()[7], m_tableMetadata->GetColumnNames()[8], m_tableMetadata->GetColumnNames()[9], m_tableMetadata->GetColumnNames()[10], m_tableMetadata->GetColumnNames()[0], m_tableMetadata->GetRelationShips().begin()->first, m_tableMetadata->GetRelationShips().begin()->second.OtherTablePrimaryKeyName);

  query.prepare(createTableString);

  if (!query.exec())
    RUNTIME_ERROR(query.lastError().text().toStdString());

  return this;
}

