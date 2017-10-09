#pragma once

#include <qstring.h>
#include <StaticGameObjectDbInfo.h>

/*
* Static game object on map Db Info
*/
struct SGOOnMapDbInfo
{
  int id;
  int staticGameObjectId;
  QString instanceName;
  StaticGameObjectDbInfo staticGameObjectDbInfo;
};

