#pragma once

#include <memory>
#include "IRepository.h"
#include "StaticGameObject.h"
#include "StaticGORepository.h"

class DALDependencyResolver
{
public:
  DALDependencyResolver();
  virtual ~DALDependencyResolver();
  static IRepository<StaticGameObject>* GetStaticGameObjectRepository() { return new StaticGORepository(); }
};
