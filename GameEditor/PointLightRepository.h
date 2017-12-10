#pragma once

#include "PointLightMetadata.h"
#include "QtRepository.h"

class PointLightRepository :
  public QtRepository<PointLightDbInfo>
{
public:
  PointLightRepository();
  virtual ~PointLightRepository();
  virtual IRepository<PointLightDbInfo>* Initialize(std::string connectionName) override;
};

