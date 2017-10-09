#pragma once

#include "SGOOnMapDbInfo.h"

struct SGOOnMapBLL
  : public SGOOnMapDbInfo
{
  int id;
  int staticGameObjectId;
  QString instanceName;
  QString SGOName;
};