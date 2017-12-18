#pragma once

#include <qstring.h>
#include <StaticGameObjectDbInfo.h>

class PointLightDbInfo
{
public:
  int id;
  QString name;
  int staticGameObjectId = 0;
  StaticGameObjectDbInfo staticGameObjectDbInfo;
  float relativePosX = 0.0f;
  float relativePosY = 0.0f;
  float relativePosZ = 0.0f;
  float red = 1.0f;
  float green = 1.0f;
  float blue = 1.0f;
  float linearAttenuation;
  float quadraticAttenuation;
  int countOnMap = 0;
};

