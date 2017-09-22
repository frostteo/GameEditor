#pragma once

#include <memory>
#include "IRepository.h"
#include "StaticGameObjectDbInfo.h"
#include "StaticGORepository.h"

class DALDependencyResolver
{
public:
  DALDependencyResolver();
  virtual ~DALDependencyResolver();
  static IRepository<StaticGameObjectDbInfo>* GetStaticGameObjectRepository() { return new StaticGORepository(); }
};
