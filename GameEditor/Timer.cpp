#include "Timer.h"

const std::string Timer::getCurrentTime()
{
  const int charBufferSize = 50;
  char timeBufferChar[charBufferSize];
  time_t seconds = time(NULL);
  tm timeStructure;

  localtime_s(&timeStructure, &seconds);

  strftime(timeBufferChar, charBufferSize, m_timeFormat.c_str(), &timeStructure);
  return std::string(timeBufferChar);
}

void Timer::setTimeFormat(const std::string &timeFormat)
{
  m_timeFormat = timeFormat;
}
