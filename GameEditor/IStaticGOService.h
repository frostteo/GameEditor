#pragma once

#include <qlist.h>
#include "StaticGameObject.h"

class IStaticGOService
{
public:
  virtual ~IStaticGOService() {}
  virtual QList<StaticGameObject> GetStaticGameObjects() = 0;
  virtual void CreateStaticGameObject(StaticGameObject& gameObject) = 0;
  virtual void UpdateStaticGameObject(StaticGameObject& gameObject) = 0;
  virtual void DeleteStaticGameObject(int id) = 0;
};

