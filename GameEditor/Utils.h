#pragma once

#include <string>

class Utils
{
public:
  Utils();
  virtual ~Utils();

  template <class T>
  static std::string Join(const T& container, const std::string& glue);
};

template <class T>
std::string Utils::Join(const T& container, const std::string& glue)
{
  std::string resultStr = "";
  int index = 0;
  for (auto &elem : container)
  {
    resultStr += elem;
    if (index != container.size() - 1)
      resultStr += glue;
    ++index;
  }
 
  return resultStr;
}