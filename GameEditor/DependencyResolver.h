#pragma once

#include <memory>
#include "IStaticGOService.h"
#include "StaticGOService.h"
#include "ISGOOnMapService.h"
#include "SGOOnMapService.h"
#include "IPointLightService.h"
#include "PointLightService.h"
#include "IPointLightOnMapService.h"
#include "PointLightOnMapService.h"

class DependencyResolver
{
public:
  DependencyResolver();
  virtual ~DependencyResolver();
  static IStaticGOService* GetStaticGOService();
  static ISGOOnMapService* GetSGOOnMapService();
  static IPointLightService* GetPointLightService();
  static IPointLightOnMapService* GetPointLightOnMapService();
};

