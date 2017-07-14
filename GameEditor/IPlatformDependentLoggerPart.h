#pragma once

#include <string>

class IPlatformDependentLoggerPart {
public:
  virtual void ShowCriticalMessage(const std::string& message) = 0;
  virtual bool Dialog(const std::string& title, const std::string& message) = 0;
};