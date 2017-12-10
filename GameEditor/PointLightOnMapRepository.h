#pragma once

#include "PointLightOnMapMetadata.h"
#include "QtRepository.h"

class PointLightOnMapRepository :
  public QtRepository<PointLightOnMapDbInfo>
{
public:
  PointLightOnMapRepository();
  virtual ~PointLightOnMapRepository();
  virtual IRepository<PointLightOnMapDbInfo>* Initialize(std::string connectionName) override;
};

