#pragma once

#include <qlist.h>
#include <vector>
#include <string>
#include "StaticGameObject.h"
#include "GetParameters.h"
#include "PagingInfo.h"

class IStaticGOService
{
public:
  virtual ~IStaticGOService() {}
  virtual QList<StaticGameObject> GetStaticGameObjects() = 0;
  virtual void CreateStaticGameObject(StaticGameObject& gameObject) = 0;
  virtual void UpdateStaticGameObject(StaticGameObject& gameObject) = 0;
  virtual void DeleteStaticGameObject(int id) = 0;
  virtual QList<StaticGameObject> GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string name = "", std::string model = "", std::string material = "") = 0;
};

