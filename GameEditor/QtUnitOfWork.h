#pragma once

#include <QSqlDatabase>
#include <memory>
#include "IUnitOfWork.h"
#include "QtUtils.h"
#include "IRepository.h"
#include "StaticGameObjectDbInfo.h"
#include "DALDependencyResolver.h"
#include "StaticGORepository.h"
#include "SGOOnMapRepository.h"
#include "PointLightRepository.h"
#include "PointLightOnMapRepository.h"

class Logger;

class QtUnitOfWork :
  public IUnitOfWork
{
protected:
  std::string m_connectionName;
  QSqlDatabase m_db;
  std::shared_ptr< IRepository<StaticGameObjectDbInfo> > m_staticGORepository;
  std::shared_ptr< IRepository<SGOOnMapDbInfo> > m_SGOOnMapRepository;
  std::shared_ptr< IRepository<PointLightDbInfo> > m_pointLightRepository;
  std::shared_ptr< IRepository<PointLightOnMapDbInfo> > m_pointLightOnMapRepository;
public:
  QtUnitOfWork();
  virtual ~QtUnitOfWork();
  virtual void Initialize(std::string hostName, std::string databaseName, std::string connectionName) override;
  virtual std::shared_ptr< IRepository<StaticGameObjectDbInfo> > GetStaticGORepository() override;
  virtual std::shared_ptr< IRepository<SGOOnMapDbInfo> > GetSGOOnMapRepository() override;
  virtual std::shared_ptr< IRepository<PointLightDbInfo> > GetPointLightRepository() override;
  virtual std::shared_ptr< IRepository<PointLightOnMapDbInfo> > GetPointLightOnMapRepository() override;
  virtual QSqlDatabase GetDatabase() override;
};

