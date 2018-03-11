#pragma once

#include <map>
#include <functional> 
#include <string>
#include <memory>
#include "Uncopyable.h"

template<typename T> class SharedResourcesFactory : private Uncopyable
{
private:
  typedef std::map<std::string, std::unique_ptr<T>, std::less<>> resourceFactoryMap;
private:
  resourceFactoryMap m_resource_map;
protected:
  virtual T* GetNewResource(const std::string& filename) = 0;
public:
  SharedResourcesFactory() = default;
  virtual ~SharedResourcesFactory() = default;
  T* GetResource(const std::string& filename);
  void Shutdown();
};

template <typename T>
void SharedResourcesFactory<T>::Shutdown()
{
  m_resource_map.clear();
}
template <typename T>
T* SharedResourcesFactory<T>::GetResource(const std::string& filename)
{
  auto element = m_resource_map.find(filename);

  if (element == m_resource_map.end())
  {
    std::unique_ptr<T> newResource(GetNewResource(filename));
    m_resource_map[filename] = std::move(newResource);
    return m_resource_map[filename].get();
  }

  return element->second.get();
}
