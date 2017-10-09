#pragma once

#include "ISGOOnMapService.h"
#include "IUnitOfWork.h"
#include "BLLDependencyResolver.h"
#include "Utils.h"
#include "SGOMetadata.h"

class SGOOnMapService : public ISGOOnMapService
{
protected:
  IUnitOfWork* m_unitOfWork;
  SGOMetadata m_SGOMetadata;
public:
  SGOOnMapService();
  virtual ~SGOOnMapService();
  virtual SGOOnMapBLL Get(int id) override;
  virtual QList<SGOOnMapDbInfo> GetAll() override;
  virtual void Create(SGOOnMapDbInfo& gameObject) override;
  virtual void Update(SGOOnMapDbInfo& gameObject) override;
  virtual void Delete(int id) override;
  virtual QList<SGOOnMapBLL> GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string SGOName = "", std::string instanceName = "") override;
};

