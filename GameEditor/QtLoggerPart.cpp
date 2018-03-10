#include "QtLoggerPart.h"

void QtLoggerPart::ShowCriticalMessage(const std::string& message) const
{
  QMessageBox::critical(nullptr, "critical error", message.c_str());
}

bool QtLoggerPart::Dialog(const std::string& title, const std::string& message) const
{
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(nullptr, title.c_str(), message.c_str(), QMessageBox::Yes | QMessageBox::No);

  if (reply == QMessageBox::Yes)
    return true;

  return false;
}
