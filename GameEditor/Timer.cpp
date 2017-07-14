#include "Timer.h"


Timer::Timer()
{
}


Timer::~Timer()
{
}

const std::string & Timer::getCurrentTime()
{
  const int charBufferSize = 50;
  char timeBufferChar[charBufferSize];
  time_t seconds = time(NULL);
  tm timeStructure;

  localtime_s(&timeStructure, &seconds);

  strftime(timeBufferChar, charBufferSize, m_timeFormat.c_str(), &timeStructure);
  m_CurrentTime = std::string(timeBufferChar);
  return m_CurrentTime;
}

void Timer::setTimeFormat(std::string &timeFormat)
{
  m_timeFormat = timeFormat;
}
