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
  static std::shared_ptr<IStaticGOService> GetStaticGOService();
  static std::shared_ptr<ISGOOnMapService> GetSGOOnMapService();
  static std::shared_ptr<IPointLightService> GetPointLightService();
  static std::shared_ptr<IPointLightOnMapService> GetPointLightOnMapService();
};

