#include "DALDependencyResolver.h"


DALDependencyResolver::DALDependencyResolver()
{
}

DALDependencyResolver::~DALDependencyResolver()
{
}

std::shared_ptr< IRepository<StaticGameObjectDbInfo> > DALDependencyResolver::GetStaticGameObjectRepository()
{ 
  static auto repository = std::make_shared<StaticGORepository>();
  return repository;
}

std::shared_ptr< IRepository<SGOOnMapDbInfo> > DALDependencyResolver::GetSGOOnMapRepository()
{
  static auto repository = std::make_shared<SGOOnMapRepository>();
  return repository;
}

std::shared_ptr< IRepository<PointLightDbInfo> > DALDependencyResolver::GetPointLightRepository() 
{
  static auto repository = std::make_shared<PointLightRepository>();
  return repository;
}

std::shared_ptr< IRepository<PointLightOnMapDbInfo> > DALDependencyResolver::GetPointLightOnMapRepository()
{ 
  static auto repository = std::make_shared<PointLightOnMapRepository>();
  return repository;
}