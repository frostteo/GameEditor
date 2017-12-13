#pragma once

#include <QSqlDatabase>
#include <memory>
#include "IUnitOfWork.h"
#include "Logger.h"
#include "QtUtils.h"
#include "IRepository.h"
#include "StaticGameObjectDbInfo.h"
#include "DALDependencyResolver.h"
#include "StaticGORepository.h"
#include "SGOOnMapRepository.h"
#include "PointLightRepository.h"
#include "PointLightOnMapRepository.h"

class QtUnitOfWork :
  public IUnitOfWork
{
protected:
  std::string m_connectionName;
  QSqlDatabase m_db;
  std::unique_ptr<IRepository<StaticGameObjectDbInfo>> m_staticGORepository;
  std::unique_ptr<IRepository<SGOOnMapDbInfo>> m_SGOOnMapRepository;
  std::unique_ptr<IRepository<PointLightDbInfo>> m_pointLightRepository;
  std::unique_ptr<IRepository<PointLightOnMapDbInfo>> m_pointLightOnMapRepository;
public:
  QtUnitOfWork();
  virtual ~QtUnitOfWork();
  virtual void Initialize(std::string hostName, std::string databaseName, std::string connectionName) override;
  virtual IRepository<StaticGameObjectDbInfo>* GetStaticGORepository() override;
  virtual IRepository<SGOOnMapDbInfo>* GetSGOOnMapRepository() override;
  virtual IRepository<PointLightDbInfo>* GetPointLightRepository() override;
  virtual IRepository<PointLightOnMapDbInfo>* GetPointLightOnMapRepository() override;
  virtual QSqlDatabase GetDatabase() override;
};

