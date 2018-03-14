#include "DependencyResolver.h"


DependencyResolver::DependencyResolver()
{
}


DependencyResolver::~DependencyResolver()
{
}

std::shared_ptr<IStaticGOService> DependencyResolver::GetStaticGOService()
{
  static auto sgoService = std::make_shared<StaticGOService>();
  return sgoService;
}

std::shared_ptr<ISGOOnMapService> DependencyResolver::GetSGOOnMapService()
{
  static auto sgoOnMapService = std::make_shared<SGOOnMapService>();
  return sgoOnMapService;
}

std::shared_ptr<IPointLightService> DependencyResolver::GetPointLightService()
{
  static auto pointLightService = std::make_shared<PointLightService>();
  return pointLightService;
}

std::shared_ptr<IPointLightOnMapService> DependencyResolver::GetPointLightOnMapService()
{
  static auto pointLightOnMapService = std::make_shared<PointLightOnMapService>();
  return pointLightOnMapService;
}