#pragma once

#include <windows.h>
#include "Logger.h"
#include "Singleton.h"

class HighPerformanceTimer : public Singleton<HighPerformanceTimer>
{
private:
  INT64 m_frequency;
  float m_ticksPerMs;
  INT64 m_startTime;
  float m_frameTime;
public:
  HighPerformanceTimer();
  virtual ~HighPerformanceTimer();

  void Initialize();
  void Frame();

  float GetTime();
};

