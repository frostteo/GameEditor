#pragma once

#include <memory>
#include "IUnitOfWork.h"
#include "QtUnitOfWork.h"

class BLLDependencyResolver
{
public:
  BLLDependencyResolver();
  virtual ~BLLDependencyResolver();
  static IUnitOfWork* GetUnitOfWork();
};

