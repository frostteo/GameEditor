#pragma once

#include <QMessageBox>
#include "IPlatformDependentLoggerPart.h"

class QtLoggerPart :
  public IPlatformDependentLoggerPart
{
public:
  QtLoggerPart();
  virtual ~QtLoggerPart();
  virtual void ShowCriticalMessage(const std::string& message) override;
  virtual bool Dialog(const std::string& title, const std::string& message) override;
};

