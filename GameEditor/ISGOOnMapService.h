#pragma once

#include <qlist.h>
#include <string>
#include "GetParameters.h"
#include "PagingInfo.h"
#include "SGOOnMapDbInfo.h"

class ISGOOnMapService
{
public:
  virtual ~ISGOOnMapService() {}
  virtual SGOOnMapDbInfo Get(int id) = 0;
  virtual QList<SGOOnMapDbInfo> GetAll() = 0;
  virtual int Create(SGOOnMapDbInfo& gameObject) = 0;
  virtual void Update(SGOOnMapDbInfo& gameObject) = 0;
  virtual void Delete(int id) = 0;
  virtual QList<SGOOnMapDbInfo> GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string SGOName = "", std::string instanceName = "") = 0;
};
