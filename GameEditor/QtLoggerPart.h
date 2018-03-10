#pragma once

#include <QMessageBox>
#include "IPlatformDependentLoggerPart.h"

class QtLoggerPart :
  public IPlatformDependentLoggerPart
{
public:
  QtLoggerPart() = default;
  virtual ~QtLoggerPart() = default;
  virtual void ShowCriticalMessage(const std::string& message) const override;
  virtual bool Dialog(const std::string& title, const std::string& message) const override;
};

