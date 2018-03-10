#pragma once
#include <ctime>
#include <string>
#include "Uncopyable.h"

class Timer : private Uncopyable
{
private:
  std::string m_timeFormat = "%A, %B %d, %Y %H:%M:%S";
public:
  Timer() = default;
  virtual ~Timer() = default;
  const std::string getCurrentTime();
  void setTimeFormat(const std::string &timeFormat);
};