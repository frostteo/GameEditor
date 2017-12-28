#pragma once

#include "IPointLightService.h"
#include "IUnitOfWork.h"
#include "BLLDependencyResolver.h"
#include "Utils.h"
#include "PointLightMetadata.h"

class PointLightService :
  public IPointLightService
{
protected:
  IUnitOfWork* m_unitOfWork;
  SGOMetadata m_SGOMetadata;
  PointLightMetadata m_pointLightMetadata;
public:
  PointLightService();
  virtual ~PointLightService();
  virtual PointLightDbInfo Get(int id) override;
  virtual QList<PointLightDbInfo> GetAll() override;
  virtual int Create(PointLightDbInfo& pointLight) override;
  virtual void Update(PointLightDbInfo& pointLight) override;
  virtual void Delete(int id) override;
  virtual QList<PointLightDbInfo> GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string name = "", std::string sgoName = "") override;
  virtual QList<PointLightDbInfo> GetPointLightsBySgoId(int id) override;
};

