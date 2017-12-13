#pragma once

#include "IPointLightOnMapService.h"
#include "IUnitOfWork.h"
#include "BLLDependencyResolver.h"
#include "Utils.h"
#include "PointLightMetadata.h"
#include "SGOMetadata.h"

class PointLightOnMapService : public IPointLightOnMapService
{
protected:
  IUnitOfWork* m_unitOfWork;
  PointLightMetadata m_pointLightMetadata;
  SGOMetadata m_sgoMetadata;
  PointLightOnMapMetadata m_pointLightOnMapMetadata;
protected:
  void IncrementPointLightCount(int id);
  void DecrementPointLightCount(int id);
public:
  virtual PointLightOnMapDbInfo Get(int id) override;
  virtual QList<PointLightOnMapDbInfo> GetAll() override;
  virtual int Create(PointLightOnMapDbInfo& gameObject) override;
  virtual void Update(PointLightOnMapDbInfo& gameObject) override;
  virtual void Delete(int id) override;
  virtual QList<PointLightOnMapDbInfo> GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string instanceName = "", std::string pointLightName = "", std::string sgoName = "") override;
  PointLightOnMapService();
  virtual ~PointLightOnMapService();
};

