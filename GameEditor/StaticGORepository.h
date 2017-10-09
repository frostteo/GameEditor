#pragma once

#include "SGOMetadata.h"
#include "QtRepository.h"

class StaticGORepository :
  public QtRepository<StaticGameObjectDbInfo>
{
public:
  StaticGORepository();
  virtual ~StaticGORepository() {}
  virtual IRepository<StaticGameObjectDbInfo>* Initialize(std::string connectionName) override;
};

