#pragma once
#include <ctime>
#include <string>

class Timer
{
private:
  std::string m_CurrentTime;
  std::string m_timeFormat = "%A, %B %d, %Y %H:%M:%S";
public:
  Timer();
  const std::string &getCurrentTime();
  void setTimeFormat(std::string &timeFormat);
  virtual ~Timer();
};