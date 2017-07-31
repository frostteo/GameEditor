#include "GameEditor.h"
#include <QtWidgets/QApplication>
#include "QtGameFrameworkTest.h"
#include "Logger.h"
#include <qmessagebox.h>
#include "QtLoggerPart.h"
#include "QtUnitOfWork.h"
#include "IUnitOfWork.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Logger::get().SetPlatformDependentLoggerPart(new QtLoggerPart());
    try {
      GameEditor w;
      w.show();
     /* QtGameFrameworkTest w;
      w.show();*/
      return a.exec();
    }
    catch (std::runtime_error& e)
    {
      Logger::get().LogMessage(std::string(e.what()));
      Logger::get().ShowCriticalMessage(e.what());
    }
 
}
