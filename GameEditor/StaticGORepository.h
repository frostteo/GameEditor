#pragma once

#include "StaticGameObject.h"
#include "QtRepository.h"

class StaticGORepository :
  public QtRepository<StaticGameObject>
{
protected:
  virtual std::vector<StaticGameObject> QueryToEntities(QSqlQuery* query) override;
  virtual QString GetFieldByName(const StaticGameObject& entity, QString name) override;
public:
  StaticGORepository();
  virtual ~StaticGORepository();
  virtual IRepository<StaticGameObject>* Initialize(std::string connectionName) override;
};

