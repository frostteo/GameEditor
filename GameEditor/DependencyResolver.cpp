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
