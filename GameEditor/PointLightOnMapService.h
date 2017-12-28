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
  const static int DEFAUT_POINT_LIGHT_SGO = 81;

  IUnitOfWork* m_unitOfWork;
  PointLightMetadata m_pointLightMetadata;
  SGOMetadata m_sgoMetadata;
  PointLightOnMapMetadata m_pointLightOnMapMetadata;
  SGOOnMapMetadata m_sgoOnMapMetadata;
protected:
  void IncrementPointLightCount(int id);
  void DecrementPointLightCount(int id);
public:
  virtual PointLightOnMapDbInfo Get(int id) override;
  virtual QList<PointLightOnMapDbInfo> GetAll() override;
  virtual int Create(PointLightOnMapDbInfo& gameObject) override;
  virtual void Update(PointLightOnMapDbInfo& gameObject) override;
  virtual void Delete(int id) override;
  PointLightOnMapService();
  virtual ~PointLightOnMapService();
  virtual PointLightOnMapDbInfo GetBySgoOnMapId(int id) override;
  virtual QList<PointLightOnMapDbInfo> GetByPointLightId(int id) override;
  virtual StaticGameObjectDbInfo GetDefaultPointLightSgo() override;
};

