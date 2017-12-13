#pragma once

#include <string>
#include "IRepository.h"
#include "StaticGameObjectDbInfo.h"
#include "SGOOnMapDbInfo.h"
#include "PointLightDbInfo.h"
#include "PointLightOnMapDbInfo.h"
#include <QSqlDatabase.h>

class IUnitOfWork 
{
public:
  IUnitOfWork() {}
  virtual ~IUnitOfWork() {}
  virtual void Initialize(std::string hostName, std::string databaseName, std::string connectionName) = 0;
  virtual IRepository<StaticGameObjectDbInfo>* GetStaticGORepository() = 0;
  virtual IRepository<SGOOnMapDbInfo>* GetSGOOnMapRepository() = 0;
  virtual IRepository<PointLightDbInfo>* GetPointLightRepository() = 0;
  virtual IRepository<PointLightOnMapDbInfo>* GetPointLightOnMapRepository() = 0;
  virtual QSqlDatabase GetDatabase() = 0; //TODO FHolod: изначально хотелось бы не иметь зависимостей от Qt в этом классе
};