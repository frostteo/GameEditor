#include "Logger.h"

const std::string Logger::cantReadFile = "Cant read file: ";

Logger::Logger()
{
  m_logFile.open(m_filename, std::ios::out | std::ios::app);
}


Logger::~Logger()
{
  m_logFile.close();

  if (m_platformDependentLoggerPart)
    delete m_platformDependentLoggerPart;
}

void Logger::LogMessage(const std::string& message)
{
  m_logFile << "time: " << m_timer.getCurrentTime() << ", info: " << message << std::endl;
}

std::string Logger::GetErrorTraceMessage(const std::string& info, const std::string& filename, const int lineNumber)
{
  std::stringstream strStream;
  strStream << "time: " << m_timer.getCurrentTime() << ", filename: " << filename << ", number of code line: " << lineNumber
    << ", info: " << info << std::endl;
  return strStream.str();
}

void Logger::LogMessage(const std::string& info, const std::string& filename, const int lineNumber)
{
  m_logFile << GetErrorTraceMessage(info, filename, lineNumber);
}

void Logger::LogMessageWithExceptionDialog(const std::string& info, const std::string& filename, const int lineNumber)
{
  bool accepted;
  std::string errorInfo = GetErrorTraceMessage(info, filename, lineNumber);
  LogMessage(errorInfo);
 
  accepted = m_platformDependentLoggerPart->Dialog("Non critical error", errorInfo + " Are you sure you want to continue?");

  if (!accepted)
    throw std::runtime_error(errorInfo + " User refuged continue.");
}

void Logger::ShowCriticalMessage(const std::string& message)
{
  m_platformDependentLoggerPart->ShowCriticalMessage(message);
}