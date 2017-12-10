#pragma once

#include <qlist.h>
#include <string>
#include "GetParameters.h"
#include "PagingInfo.h"
#include "PointLightDbInfo.h"

class IPointLightService
{
public:
  virtual ~IPointLightService() {}
  virtual PointLightDbInfo Get(int id) = 0;
  virtual QList<PointLightDbInfo> GetAll() = 0;
  virtual int Create(PointLightDbInfo& pointLight) = 0;
  virtual void Update(PointLightDbInfo& pointLight) = 0;
  virtual void Delete(int id) = 0;
  virtual QList<PointLightDbInfo> GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string name = "", std::string sgoName = "") = 0;
};
