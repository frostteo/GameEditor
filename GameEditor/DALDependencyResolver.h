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
  static IRepository<StaticGameObjectDbInfo>* GetStaticGameObjectRepository() { return new StaticGORepository(); }
  static IRepository<SGOOnMapDbInfo>* GetSGOOnMapRepository() { return new SGOOnMapRepository(); }
  static IRepository<PointLightDbInfo>* GetPointLightRepository() { return new PointLightRepository(); }
  static IRepository<PointLightOnMapDbInfo>* GetPointLightOnMapRepository() { return new PointLightOnMapRepository(); }
};
