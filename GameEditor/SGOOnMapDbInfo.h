#pragma once

#include <qstring.h>
#include <StaticGameObjectDbInfo.h>

/*
* Static game object on map Db Info
*/
struct SGOOnMapDbInfo
{
  int id = 0;
  int staticGameObjectId;
  QString instanceName;
  StaticGameObjectDbInfo staticGameObjectDbInfo;
  float xPos = 0.0f;
  float yPos = 0.0f;
  float zPos = 0.0f;
  float xRotate = 0.0f;
  float yRotate = 0.0f;
  float zRotate = 0.0f;
  int isFrozen = 0;
};

