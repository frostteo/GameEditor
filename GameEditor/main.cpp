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
    Logger::get().SetPlatformDependentLoggerPart(new QtLoggerPart());
    try {
    
      GameEditor w;

      //GetParameters getParameters;
      //PagingInfo pagingInfo;
      //auto test = DependencyResolver::GetSGOOnMapService()->GetFiltered(getParameters, pagingInfo);


      //auto test2 = DependencyResolver::GetSGOOnMapService()->GetAll();
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
