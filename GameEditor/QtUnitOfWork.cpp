#include "QtUnitOfWork.h"


QtUnitOfWork::QtUnitOfWork()
{
}


QtUnitOfWork::~QtUnitOfWork()
{
}

void QtUnitOfWork::Initialize(std::string hostName, std::string databaseName, std::string connectionName)
{
  m_connectionName = connectionName;
  m_db = QSqlDatabase::addDatabase("QSQLITE", connectionName.c_str());
  m_db.setHostName(hostName.c_str());
  m_db.setDatabaseName(databaseName.c_str());

  if (!m_db.open())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(m_db.lastError().text().toStdString(), __FILE__, __LINE__));

  m_staticGORepository = std::unique_ptr<IRepository<StaticGameObjectDbInfo>>(
    DALDependencyResolver::GetStaticGameObjectRepository()->Initialize(connectionName)
    );
}

IRepository<StaticGameObjectDbInfo>* QtUnitOfWork::GetStaticGORepository()
{
  return m_staticGORepository.get();
}