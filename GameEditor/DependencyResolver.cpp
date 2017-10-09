#include "DependencyResolver.h"


DependencyResolver::DependencyResolver()
{
}


DependencyResolver::~DependencyResolver()
{
}

IStaticGOService* DependencyResolver::GetStaticGOService()
{
  static std::unique_ptr<IStaticGOService> service = std::unique_ptr<IStaticGOService>(new StaticGOService());
  return service.get();
}

ISGOOnMapService* DependencyResolver::GetSGOOnMapService()
{
  static std::unique_ptr<ISGOOnMapService> service2 = std::unique_ptr<ISGOOnMapService>(new SGOOnMapService());
  return service2.get();
}
