#pragma once

#include <string>
#include "IRepository.h"
#include "StaticGameObjectDbInfo.h"

class IUnitOfWork 
{
public:
  IUnitOfWork() {}
  virtual ~IUnitOfWork() {}
  virtual void Initialize(std::string hostName, std::string databaseName, std::string connectionName) = 0;
  virtual IRepository<StaticGameObjectDbInfo>* GetStaticGORepository() = 0;
};