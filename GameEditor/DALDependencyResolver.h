#pragma once

#include <memory>
#include "IRepository.h"
#include "StaticGameObjectDbInfo.h"
#include "StaticGORepository.h"
#include "SGOOnMapDbInfo.h"
#include "SGOOnMapRepository.h"
#include "PointLightRepository.h"
#include "PointLightOnMapRepository.h"

class DALDependencyResolver
{
public:
  DALDependencyResolver();
  virtual ~DALDependencyResolver();
  static std::shared_ptr< IRepository<StaticGameObjectDbInfo> > GetStaticGameObjectRepository();
  static std::shared_ptr< IRepository<SGOOnMapDbInfo> > GetSGOOnMapRepository();
  static std::shared_ptr< IRepository<PointLightDbInfo> > GetPointLightRepository();
  static std::shared_ptr< IRepository<PointLightOnMapDbInfo> > GetPointLightOnMapRepository();
};
