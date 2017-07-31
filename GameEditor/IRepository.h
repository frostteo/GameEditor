#pragma once

#include <vector>
#include <string>

template <class T>
class IRepository
{
public:
  virtual IRepository<T>* Initialize(std::string connectionName) = 0;
  virtual std::vector<T> GetAll() = 0;
  virtual T Get(int id) = 0;
  virtual void Delete(int id) = 0;
  virtual void Update(T entity) = 0;
  virtual void Create(const T& entity) = 0;
  virtual ~IRepository() {}
};

