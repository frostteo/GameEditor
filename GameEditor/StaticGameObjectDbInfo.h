#pragma once

#include <qstring.h>

class StaticGameObjectDbInfo {
public:
  int id;
  QString name;
  QString modelFileName;
  int countOnMap = 0;
  bool isService = false;
};