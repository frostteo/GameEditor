#pragma once

#include "StaticGameObject.h"
#include "QtRepository.h"
#include "Utils.h"

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
  virtual std::vector<StaticGameObject> GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string name = "", std::string model = "", std::string material = "");
};

