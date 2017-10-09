#pragma once

#include "SGOOnMapMetadata.h"
#include "QtRepository.h"

class SGOOnMapRepository :
  public QtRepository<SGOOnMapDbInfo>
{
public:
  SGOOnMapRepository();
  virtual ~SGOOnMapRepository();
  virtual IRepository<SGOOnMapDbInfo>* Initialize(std::string connectionName) override;
};

