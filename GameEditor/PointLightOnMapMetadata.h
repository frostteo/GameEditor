#pragma once

#include <algorithm>
#include "PointLightOnMapDbInfo.h"
#include "PointLightMetadata.h"

class PointLightOnMapMetadata :
  public DbTableMetadata<PointLightOnMapDbInfo>
{
protected:
  SGOMetadata m_sgoMetadata;
  PointLightMetadata m_pointLightMetadata;
protected:
  virtual void BuildJoinConditions() override;
public:
  PointLightOnMapMetadata();
  virtual ~PointLightOnMapMetadata();
  virtual void InitializeFromQuery(PointLightOnMapDbInfo& entity, QSqlQuery* query, std::vector<QString>* joinTableNames = nullptr) override;
  virtual QVariant GetFieldByName(const PointLightOnMapDbInfo& entity, QString name) override;
  virtual QString GetSelectColumnString(std::vector<QString>* joinTableNames = nullptr) override;
  virtual QString GetRelationShipAlias(QString tableName, int columnIndex) override;
};

