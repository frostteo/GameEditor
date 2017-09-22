#pragma once

#include "StaticGameObjectDbInfo.h"
#include "QtRepository.h"

class StaticGORepository :
  public QtRepository<StaticGameObjectDbInfo>
{
protected:
  virtual std::vector<StaticGameObjectDbInfo> QueryToEntities(QSqlQuery* query) override;
  virtual QString GetFieldByName(const StaticGameObjectDbInfo& entity, QString name) override;
public:
  StaticGORepository();
  virtual ~StaticGORepository();
  virtual IRepository<StaticGameObjectDbInfo>* Initialize(std::string connectionName) override;
};

