#pragma once

#include <memory>
#include "IRepository.h"
#include "StaticGameObjectDbInfo.h"
#include "StaticGORepository.h"
#include "SGOOnMapDbInfo.h"
#include "SGOOnMapRepository.h"

class DALDependencyResolver
{
public:
  DALDependencyResolver();
  virtual ~DALDependencyResolver();
  static IRepository<StaticGameObjectDbInfo>* GetStaticGameObjectRepository() { return new StaticGORepository(); }
  static IRepository<SGOOnMapDbInfo>* GetSGOOnMapRepository() { return new SGOOnMapRepository(); }
};
