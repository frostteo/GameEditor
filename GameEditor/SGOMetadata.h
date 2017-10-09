#pragma once

#include "DbTableMetadata.h"
#include "StaticGameObjectDbInfo.h"
#include "Logger.h"

class SGOMetadata :
  public DbTableMetadata<StaticGameObjectDbInfo>
{
public:
  SGOMetadata();
  virtual ~SGOMetadata();

  virtual void InitializeFromQuery(StaticGameObjectDbInfo& entity, QSqlQuery* query, std::vector<QString>* joinTableNames = nullptr) override;
  virtual QVariant GetFieldByName(const StaticGameObjectDbInfo& entity, QString name) override;
};

