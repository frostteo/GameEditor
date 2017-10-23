#pragma once

#include <qlist.h>
#include <vector>
#include <string>
#include "StaticGameObjectDbInfo.h"
#include "GetParameters.h"
#include "PagingInfo.h"

class IStaticGOService
{
public:
  virtual ~IStaticGOService() {}
  virtual StaticGameObjectDbInfo GetStaticGameObject(int id) = 0;
  virtual QList<StaticGameObjectDbInfo> GetStaticGameObjects() = 0;
  virtual int CreateStaticGameObject(StaticGameObjectDbInfo& gameObject) = 0;
  virtual void UpdateStaticGameObject(StaticGameObjectDbInfo& gameObject) = 0;
  virtual void DeleteStaticGameObject(int id) = 0;
  virtual QList<StaticGameObjectDbInfo> GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string name = "", std::string model = "") = 0;
};

