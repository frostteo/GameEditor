#pragma once

#include <qstring.h>
#include <PointLightDbInfo.h>

class PointLightOnMapDbInfo
{
public:
  int id;
  int pointLightId = 0;
  QString instanceName;
  PointLightDbInfo pointLightDbInfo;

  float xPos = 0.0f;
  float yPos = 0.0f;
  float zPos = 0.0f;
  float xRotate = 0.0f;
  float yRotate = 0.0f;
  float zRotate = 0.0f;
  bool isFrozen = false;

  float linearAttenuation;
  float quadraticAttenuation;
};

