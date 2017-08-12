#pragma once

#include <string>
#include "IRepository.h"
#include "StaticGameObject.h"
#include "StaticGORepository.h"

class IUnitOfWork 
{
public:
  IUnitOfWork() {}
  virtual ~IUnitOfWork() {}
  virtual void Initialize(std::string hostName, std::string databaseName, std::string connectionName) = 0;
  virtual StaticGORepository* GetStaticGORepository() = 0;
};