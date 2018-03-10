#include "HighPerformanceTimer.h"
#include "Logger.h"

HighPerformanceTimer::HighPerformanceTimer()
{
}


HighPerformanceTimer::~HighPerformanceTimer()
{
}

void HighPerformanceTimer::Initialize()
{
  const int milisecondsInSecond = 1000;

  // Check to see if this system supports high performance timers.
  QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
  if (m_frequency == 0)
    RUNTIME_ERROR("system doesn't supports high performance timers.");

  // Find out how many times the frequency counter ticks every millisecond.
  m_ticksPerMs = (float)(m_frequency / milisecondsInSecond);

  QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);
}

void HighPerformanceTimer::Frame()
{
  INT64 currentTime;
  float timeDifference;

  QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

  timeDifference = (float)(currentTime - m_startTime);

  m_frameTime = timeDifference / m_ticksPerMs;

  m_startTime = currentTime;
}

float HighPerformanceTimer::GetTime()
{
  return m_frameTime;
}
