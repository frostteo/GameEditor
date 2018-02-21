#pragma once

#include <map>
#include <functional> 
#include <string>

template<typename T> class SharedResourcesFactory
{
private:
  typedef std::map<std::string, T*, std::less<>> resourceFactoryMap; //TODO FHolod: maybe key must be reference or pointer
private:
  resourceFactoryMap m_resource_map;
protected:
  virtual T* GetNewResource(const std::string& filename) = 0;
public:
  SharedResourcesFactory();
  virtual ~SharedResourcesFactory();
  T* GetResource(const std::string& filename);
  void Shutdown();
};


template <typename T>
SharedResourcesFactory<T>::SharedResourcesFactory()
{
}

template <typename T>
void SharedResourcesFactory<T>::Shutdown()
{
  for (auto& element : m_resource_map)
  {
    delete element.second;
    element.second = nullptr;
  }
  m_resource_map.clear();
}

template <typename T>
SharedResourcesFactory<T>::~SharedResourcesFactory()
{
  Shutdown();
}

template <typename T>
T* SharedResourcesFactory<T>::GetResource(const std::string& filename)
{
  auto element = m_resource_map.find(filename);

  if (element == m_resource_map.end())
  {
    T* newResource = GetNewResource(filename);
    resourceFactoryMap::value_type newPair(filename, newResource);
    m_resource_map.insert(newPair);
    return newResource;
  }

  return element->second;
}
