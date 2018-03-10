#pragma once

#include "SGOMetadata.h"
#include "PointLightDbInfo.h"

class PointLightMetadata :
  public DbTableMetadata<PointLightDbInfo>
{
protected:
  SGOMetadata m_SGOMetadata;
public:
  PointLightMetadata();
  virtual ~PointLightMetadata();

  virtual void InitializeFromQuery(PointLightDbInfo& entity, QSqlQuery* query, std::vector<QString>* joinTableNames = nullptr) override;
  virtual QVariant GetFieldByName(const PointLightDbInfo& entity, QString name) override;
  virtual QString GetSelectColumnString(std::vector<QString>* joinTableNames = nullptr) override;
  virtual QString GetRelationShipAlias(QString tableName, int columnIndex) override;
  virtual QString GetDefaultOrderString() override;
};

