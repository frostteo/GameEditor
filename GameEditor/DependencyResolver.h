#pragma once

#include <memory>
#include "IStaticGOService.h"
#include "StaticGOService.h"

class DependencyResolver
{
public:
  DependencyResolver();
  virtual ~DependencyResolver();
  static IStaticGOService* GetStaticGOService();
};

