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
  static StaticGORepository* GetStaticGameObjectRepository() { return new StaticGORepository(); }
};
