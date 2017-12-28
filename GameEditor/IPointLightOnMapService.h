#pragma once

#include <qlist.h>
#include <string>
#include "GetParameters.h"
#include "PagingInfo.h"
#include "PointLightOnMapDbInfo.h"

class IPointLightOnMapService
{
public:
  virtual ~IPointLightOnMapService() {}
  virtual PointLightOnMapDbInfo Get(int id) = 0;
  virtual QList<PointLightOnMapDbInfo> GetAll() = 0;
  virtual int Create(PointLightOnMapDbInfo& gameObject) = 0;
  virtual void Update(PointLightOnMapDbInfo& gameObject) = 0;
  virtual void Delete(int id) = 0;
  virtual PointLightOnMapDbInfo GetBySgoOnMapId(int id) = 0;
  virtual QList<PointLightOnMapDbInfo> GetByPointLightId(int id) = 0;
  virtual StaticGameObjectDbInfo GetDefaultPointLightSgo() = 0;
};
