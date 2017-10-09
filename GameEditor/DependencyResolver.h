#pragma once

#include <memory>
#include "IStaticGOService.h"
#include "StaticGOService.h"
#include "ISGOOnMapService.h"
#include "SGOOnMapService.h"

class DependencyResolver
{
public:
  DependencyResolver();
  virtual ~DependencyResolver();
  static IStaticGOService* GetStaticGOService();
  static ISGOOnMapService* GetSGOOnMapService();
};

