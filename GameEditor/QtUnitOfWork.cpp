#include "QtUnitOfWork.h"
#include "Logger.h"

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
    RUNTIME_ERROR(m_db.lastError().text().toStdString());

  m_staticGORepository = std::unique_ptr<IRepository<StaticGameObjectDbInfo>>(
    DALDependencyResolver::GetStaticGameObjectRepository()->Initialize(connectionName)
    );

  m_SGOOnMapRepository = std::unique_ptr<IRepository<SGOOnMapDbInfo>>(
    DALDependencyResolver::GetSGOOnMapRepository()->Initialize(connectionName)
    );

  m_pointLightRepository = std::unique_ptr<IRepository<PointLightDbInfo>>(
    DALDependencyResolver::GetPointLightRepository()->Initialize(connectionName)
    );

  m_pointLightOnMapRepository = std::unique_ptr<IRepository<PointLightOnMapDbInfo>>(
    DALDependencyResolver::GetPointLightOnMapRepository()->Initialize(connectionName)
    );
}

IRepository<StaticGameObjectDbInfo>* QtUnitOfWork::GetStaticGORepository()
{
  return m_staticGORepository.get();
}

IRepository<SGOOnMapDbInfo>* QtUnitOfWork::GetSGOOnMapRepository()
{
  return m_SGOOnMapRepository.get();
}

IRepository<PointLightDbInfo>* QtUnitOfWork::GetPointLightRepository()
{
  return m_pointLightRepository.get();
}

IRepository<PointLightOnMapDbInfo>* QtUnitOfWork::GetPointLightOnMapRepository()
{
  return m_pointLightOnMapRepository.get();
}

QSqlDatabase QtUnitOfWork::GetDatabase()
{
  return m_db;
}