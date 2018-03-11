#pragma once

#include "Singleton.h"

#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

class IPlatformDependentLoggerPart;
class Timer;
class Logger;

#define RUNTIME_ERROR(Message) throw std::runtime_error(Logger::get().GetErrorTraceMessage(Message, __FILE__, __LINE__));
#define CANT_READ_FILE_ERROR(filename) Logger::get().LogMessageWithExceptionDialog(Logger::CANT_READ_FILE_MSG + filename, __FILE__, __LINE__);

class Logger : public Singleton<Logger>
{
  friend class Singleton<Logger>;
private:
  std::unique_ptr<Timer> m_timer;
  std::unique_ptr<IPlatformDependentLoggerPart> m_platformDependentLoggerPart;
  std::ofstream m_logFile;
  std::string m_filename = "default_log.txt";
public:
  const static std::string CANT_READ_FILE_MSG;
  const static std::string PLATFORM_DEPENDENT_PART_NOT_INSTALLED_MSG;
private:
  Logger();
  virtual ~Logger();
public:
  std::string GetErrorTraceMessage(const std::string& info, const std::string& filename, const int lineNumber) const;
  void LogMessage(const std::string& message);
  void LogMessage(const std::string& info, const std::string& filename, const int lineNumber);
  void LogMessageWithExceptionDialog(const std::string& info, const std::string& filename, const int lineNumber);
  void ShowCriticalMessage(const std::string& message);
  const std::string GetLogFileName() const { return m_filename; }
  void SetPlatformDependentLoggerPart(std::unique_ptr<IPlatformDependentLoggerPart> platformDependentLoggerPart);
  void SetLogFileName(const std::string& logFileName);
};
