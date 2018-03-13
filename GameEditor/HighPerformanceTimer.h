#pragma once

#include <windows.h>
#include "Singleton.h"

class Logger;

class HighPerformanceTimer : public Singleton<HighPerformanceTimer>
{
private:
  INT64 m_frequency;
  float m_ticksPerMs;
  INT64 m_startTime;
  float m_frameTime;
public:
  HighPerformanceTimer() = default;
  virtual ~HighPerformanceTimer() = default;

  void Initialize();
  void Frame();

  float GetTime() const;
};

