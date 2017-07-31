#pragma once

#include <QSqlDatabase>
#include <memory>
#include "IUnitOfWork.h"
#include "Logger.h"
#include "QtUtils.h"
#include "StaticGORepository.h"
#include "DALDependencyResolver.h"

class QtUnitOfWork :
  public IUnitOfWork
{
protected:
  std::string m_connectionName;
  QSqlDatabase m_db;
  std::unique_ptr<StaticGORepository> m_staticGORepository;
public:
  QtUnitOfWork();
  virtual ~QtUnitOfWork();
  virtual void Initialize(std::string hostName, std::string databaseName, std::string connectionName) override;
  virtual IRepository<StaticGameObject>* GetStaticGORepository() override;
};

