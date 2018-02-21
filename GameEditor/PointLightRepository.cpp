#include "PointLightRepository.h"


PointLightRepository::PointLightRepository()
{
}


PointLightRepository::~PointLightRepository()
{
}

IRepository<PointLightDbInfo>* PointLightRepository::Initialize(std::string connectionName)
{
  m_tableMetadata = std::unique_ptr<PointLightMetadata>(new PointLightMetadata());
  m_defaultOrderField = m_tableMetadata->GetDefaultOrderString();

  QtRepository<PointLightDbInfo>::Initialize(connectionName);
  QSqlQuery query(GetDatabase());

  QString createTableString = QString("CREATE TABLE IF NOT EXISTS %1 (%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 TEXT, %4 INTEGER, %5 REAL NOT NULL, %6 REAL NOT NULL, %7 REAL NOT NULL, %8 REAL NOT NULL, %9 REAL NOT NULL, ").arg(m_tableMetadata->GetTableName(), m_tableMetadata->GetKeyColumnName(), m_tableMetadata->GetColumnNames()[0], m_tableMetadata->GetColumnNames()[1], m_tableMetadata->GetColumnNames()[2], m_tableMetadata->GetColumnNames()[3], m_tableMetadata->GetColumnNames()[4], m_tableMetadata->GetColumnNames()[5], m_tableMetadata->GetColumnNames()[6]);

  createTableString = QString("%1 %2 REAL NOT NULL, %3 REAL NOT NULL, %4 REAL NOT NULL, %5 INTEGER NOT NULL, %6 INTEGER NOT NULL, FOREIGN KEY(%7) REFERENCES %8(%9) ON DELETE SET NULL ON UPDATE SET NULL)").arg(createTableString, m_tableMetadata->GetColumnNames()[7], m_tableMetadata->GetColumnNames()[8], m_tableMetadata->GetColumnNames()[9], m_tableMetadata->GetColumnNames()[10], m_tableMetadata->GetColumnNames()[11], m_tableMetadata->GetColumnNames()[1], m_tableMetadata->GetRelationShips().begin()->first, m_tableMetadata->GetRelationShips().begin()->second.OtherTablePrimaryKeyName);

  query.prepare(createTableString);

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(query.lastError().text().toStdString(), __FILE__, __LINE__));

  return this;
}