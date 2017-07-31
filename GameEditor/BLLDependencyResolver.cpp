#include "BLLDependencyResolver.h"


BLLDependencyResolver::BLLDependencyResolver()
{
}


BLLDependencyResolver::~BLLDependencyResolver()
{
}

IUnitOfWork* BLLDependencyResolver::GetUnitOfWork()
{
  static std::unique_ptr<IUnitOfWork> unitOfWork = std::unique_ptr<IUnitOfWork>(new QtUnitOfWork());
  return unitOfWork.get();
}
