#pragma once

#include <algorithm>
#include "DbTableMetadata.h"
#include "SGOOnMapDbInfo.h"
#include "SGOMetadata.h"

class SGOOnMapMetadata :
  public DbTableMetadata<SGOOnMapDbInfo>
{
protected:
  SGOMetadata m_SGOMetadata;
public:
  SGOOnMapMetadata();
  virtual ~SGOOnMapMetadata();
  virtual void InitializeFromQuery(SGOOnMapDbInfo& entity, QSqlQuery* query, std::vector<QString>* joinTableNames = nullptr) override;
  virtual QVariant GetFieldByName(const SGOOnMapDbInfo& entity, QString name) override;
  virtual QString GetSelectColumnString(std::vector<QString>* joinTableNames = nullptr) override;
};

