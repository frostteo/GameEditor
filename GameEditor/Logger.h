#pragma once

#include "Singleton.h"
#include "Timer.h"
#include <string>
#include <fstream>
#include <sstream>
#include "IPlatformDependentLoggerPart.h"

class Logger : public Singleton<Logger>
{
  friend class Singleton<Logger>;
private:
  Timer m_timer;
  std::string m_filename = "gameEditorLog.txt";
  std::ofstream m_logFile;
  IPlatformDependentLoggerPart* m_platformDependentLoggerPart;
public:
  const static std::string cantReadFile;
public:
  Logger();
  virtual ~Logger();
  std::string GetErrorTraceMessage(const std::string& info, const std::string& filename, const int lineNumber);
  void LogMessage(std::string& message);
  void LogMessage(const std::string& info, const std::string& filename, const int lineNumber);
  void LogMessageWithExceptionDialog(const std::string& info, const std::string& filename, const int lineNumber);
  void ShowCriticalMessage(const std::string& message);
  void SetPlatformDependentLoggerPart(IPlatformDependentLoggerPart* platformDependentLoggerPart) { m_platformDependentLoggerPart = platformDependentLoggerPart; }
};

