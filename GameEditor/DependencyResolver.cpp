#include "DependencyResolver.h"


DependencyResolver::DependencyResolver()
{
}


DependencyResolver::~DependencyResolver()
{
}

IStaticGOService* DependencyResolver::GetStaticGOService()
{
  static std::unique_ptr<IStaticGOService> sgoService = std::unique_ptr<IStaticGOService>(new StaticGOService());
  return sgoService.get();
}

ISGOOnMapService* DependencyResolver::GetSGOOnMapService()
{
  static std::unique_ptr<ISGOOnMapService> sgoOnMapService = std::unique_ptr<ISGOOnMapService>(new SGOOnMapService());
  return sgoOnMapService.get();
}

IPointLightService* DependencyResolver::GetPointLightService()
{
  static std::unique_ptr<IPointLightService> pointLightService = std::unique_ptr<IPointLightService>(new PointLightService());
  return pointLightService.get();
}

IPointLightOnMapService* DependencyResolver::GetPointLightOnMapService()
{
  static std::unique_ptr<IPointLightOnMapService> pointLightOnMapService = std::unique_ptr<IPointLightOnMapService>(new PointLightOnMapService());
  return pointLightOnMapService.get();
}