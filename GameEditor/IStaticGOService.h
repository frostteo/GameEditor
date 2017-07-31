#pragma once

#include <qlist.h>
#include "StaticGameObject.h"

class IStaticGOService
{
public:
  virtual ~IStaticGOService() {}
  virtual QList<StaticGameObject> GetStaticGameObjects() = 0;
  virtual void CreateStaticGameObject(const StaticGameObject& gameObject) = 0;
};

