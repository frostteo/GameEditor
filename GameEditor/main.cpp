#include "GameEditor.h"
#include <QtWidgets/QApplication>
#include "QtGameFrameworkTest.h"
#include "Logger.h"
#include <qmessagebox.h>
#include "QtLoggerPart.h"

#include "DependencyResolver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto platformDependentLoggerPart = std::unique_ptr<QtLoggerPart>(new QtLoggerPart());
    Logger::get().SetPlatformDependentLoggerPart(std::move(platformDependentLoggerPart));
    Logger::get().SetLogFileName("gameEditorLog.txt");

    try {
      GameEditor w;

      w.showMaximized();
     /* QtGameFrameworkTest w2;
      w2.show();*/
      return a.exec();
    }
    catch (std::runtime_error& e)
    {
      Logger::get().LogMessage(std::string(e.what()));
      Logger::get().ShowCriticalMessage(e.what());
    }
 
}
