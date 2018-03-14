#include "BLLDependencyResolver.h"


BLLDependencyResolver::BLLDependencyResolver()
{
}


BLLDependencyResolver::~BLLDependencyResolver()
{
}

std::shared_ptr<IUnitOfWork> BLLDependencyResolver::GetUnitOfWork()
{
  static auto unitOfWork = std::make_shared<QtUnitOfWork>();;
  return unitOfWork;
}
