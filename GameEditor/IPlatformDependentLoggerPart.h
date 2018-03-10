#pragma once

#include <string>
#include "Uncopyable.h"

class IPlatformDependentLoggerPart : private Uncopyable {
public:
  virtual void ShowCriticalMessage(const std::string& message) const = 0;
  virtual bool Dialog(const std::string& title, const std::string& message) const = 0;
};