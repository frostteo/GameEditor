#pragma once

#include <vector>
#include <string>
#include "GetParameters.h"
#include "PagingInfo.h"

template <class T>
class IRepository
{
public:
  virtual IRepository<T>* Initialize(std::string connectionName) = 0;
  virtual std::vector<T> GetAll() = 0;
  virtual std::vector<T> GetAll(GetParameters& parameters, PagingInfo& pagingInfo) = 0;
  virtual T Get(int id) = 0;
  virtual void Delete(int id) = 0;
  virtual void Update(T& entity) = 0;
  virtual void Create(T& entity) = 0;
  virtual ~IRepository() {}
};

