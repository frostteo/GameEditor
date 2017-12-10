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

      GetParameters getParameters;
      PagingInfo pagingInfo;

      PointLightDbInfo pointLight;
      pointLight.name = "test2";
      pointLight.staticGameObjectId = 40;
      pointLight.linearAttenuation = 0.7f;
      pointLight.quadraticAttenuation = 1.8f;
      //DependencyResolver::GetPointLightService()->Create(pointLight);
      /*PointLightDbInfo pointLight = DependencyResolver::GetPointLightService()->Get(1);
      pointLight.name = "Fedor test";
      DependencyResolver::GetPointLightService()->Update(pointLight);*/
      //DependencyResolver::GetPointLightService()->Delete(1);

      PointLightOnMapDbInfo pointLightOnMap;
     /* pointLightOnMap.pointLightId = 1;
      pointLightOnMap.instanceName = "test2 instance";
      pointLightOnMap.linearAttenuation = pointLight.linearAttenuation;
      pointLightOnMap.quadraticAttenuation = pointLight.quadraticAttenuation;
      pointLightOnMap.xPos = 10;
      pointLightOnMap.yPos = 50;
      pointLightOnMap.zPos = 134;*/
      //DependencyResolver::GetPointLightOnMapService()->Create(pointLightOnMap);
     /* pointLightOnMap = DependencyResolver::GetPointLightOnMapService()->Get(1);
      pointLightOnMap.isFrozen = false;
      pointLightOnMap.xRotate = 524;
      DependencyResolver::GetPointLightOnMapService()->Delete(1);
      auto test2 = DependencyResolver::GetPointLightOnMapService()->GetAll();*/
      //auto test = DependencyResolver::GetPointLightService()->Get(1);

      auto test2 = DependencyResolver::GetPointLightOnMapService()->GetFiltered(getParameters, pagingInfo, "", "test", "lamp");
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
