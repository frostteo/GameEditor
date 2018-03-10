#include "Logger.h"
#include "Timer.h"
#include "IPlatformDependentLoggerPart.h"

const std::string Logger::CANT_READ_FILE_MSG = "Cant read file: ";
const std::string Logger::PLATFORM_DEPENDENT_PART_NOT_INSTALLED_MSG = "Platform dependent path of log not installed, can't show dialog window";

Logger::Logger() :
  m_timer(new Timer()),
  m_platformDependentLoggerPart(nullptr), 
  m_logFile()
{
  m_logFile.open(m_filename, std::ios::out | std::ios::app);
}


Logger::~Logger()
{
  m_logFile.close();
}

void Logger::LogMessage(const std::string& message)
{
  if (m_logFile.is_open())
    m_logFile << "time: " << m_timer->getCurrentTime() << ", info: " << message << std::endl;
}

std::string Logger::GetErrorTraceMessage(const std::string& info, const std::string& filename, const int lineNumber) const
{
  std::stringstream strStream;
  strStream << "time: " << m_timer->getCurrentTime() << ", filename: " << filename << ", number of code line: " << lineNumber
    << ", info: " << info << std::endl;
  return strStream.str();
}

void Logger::LogMessage(const std::string& info, const std::string& filename, const int lineNumber)
{
  if (m_logFile.is_open())
    m_logFile << GetErrorTraceMessage(info, filename, lineNumber);
}

void Logger::LogMessageWithExceptionDialog(const std::string& info, const std::string& filename, const int lineNumber)
{
  bool accepted;
  std::string errorInfo = GetErrorTraceMessage(info, filename, lineNumber);
  LogMessage(errorInfo);
 
  if (m_platformDependentLoggerPart)
  {
    accepted = m_platformDependentLoggerPart->Dialog("Non critical error", errorInfo + " Are you sure you want to continue?");

    if (!accepted)
      throw std::runtime_error(errorInfo + " User refuged continue.");
  }
  else
  {
    LogMessage(PLATFORM_DEPENDENT_PART_NOT_INSTALLED_MSG);
  }
}

void Logger::ShowCriticalMessage(const std::string& message) 
{
  if (m_platformDependentLoggerPart)
  {
    m_platformDependentLoggerPart->ShowCriticalMessage(message);
  }
  else
  {
    LogMessage(PLATFORM_DEPENDENT_PART_NOT_INSTALLED_MSG);
  }
}

void Logger::SetPlatformDependentLoggerPart(IPlatformDependentLoggerPart* platformDependentLoggerPart)
{
  m_platformDependentLoggerPart = std::unique_ptr<IPlatformDependentLoggerPart>(platformDependentLoggerPart);
}

void Logger::SetLogFileName(const std::string& logFileName)
{
  m_filename = logFileName;

  if (m_logFile.is_open())
    m_logFile.close();

  m_logFile.open(m_filename, std::ios::out | std::ios::app);
}
