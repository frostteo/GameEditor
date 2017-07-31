#pragma once

#include <memory>
#include "QtRepository.h"
#include "StaticGameObject.h"
#include "StaticGORepository.h"
#include "IUnitOfWork.h"
#include "QtUnitOfWork.h"

class DALDependencyResolver
{
public:
  DALDependencyResolver();
  virtual ~DALDependencyResolver();
  static QtRepository<StaticGameObject>* GetStaticGameObjectRepository() { return new StaticGORepository(); }
};

