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

  m_staticGORepository = std::shared_ptr<IRepository<StaticGameObjectDbInfo> >(DALDependencyResolver::GetStaticGameObjectRepository());
  m_staticGORepository->Initialize(connectionName);

  m_SGOOnMapRepository = std::shared_ptr<IRepository<SGOOnMapDbInfo> >(DALDependencyResolver::GetSGOOnMapRepository());
  m_SGOOnMapRepository->Initialize(connectionName);

  m_pointLightRepository = std::shared_ptr<IRepository<PointLightDbInfo> >(DALDependencyResolver::GetPointLightRepository());
  m_pointLightRepository->Initialize(connectionName);

  m_pointLightOnMapRepository = std::shared_ptr<IRepository<PointLightOnMapDbInfo> >(DALDependencyResolver::GetPointLightOnMapRepository());
  m_pointLightOnMapRepository->Initialize(connectionName);
}

std::shared_ptr<IRepository<StaticGameObjectDbInfo> > QtUnitOfWork::GetStaticGORepository()
{
  return m_staticGORepository;
}

std::shared_ptr<IRepository<SGOOnMapDbInfo> > QtUnitOfWork::GetSGOOnMapRepository()
{
  return m_SGOOnMapRepository;
}

std::shared_ptr<IRepository<PointLightDbInfo> > QtUnitOfWork::GetPointLightRepository()
{
  return m_pointLightRepository;
}

std::shared_ptr<IRepository<PointLightOnMapDbInfo> > QtUnitOfWork::GetPointLightOnMapRepository()
{
  return m_pointLightOnMapRepository;
}

QSqlDatabase QtUnitOfWork::GetDatabase()
{
  return m_db;
}