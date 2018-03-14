#pragma once

#include <memory>
#include "ISGOOnMapService.h"
#include "IUnitOfWork.h"
#include "BLLDependencyResolver.h"
#include "Utils.h"
#include "SGOMetadata.h"
#include "SGOOnMapMetadata.h"

class SGOOnMapService : public ISGOOnMapService
{
protected:
  std::shared_ptr<IUnitOfWork> m_unitOfWork;
  SGOMetadata m_SGOMetadata;
  SGOOnMapMetadata m_sgoOnMapMetadata;
protected:
  void IncrementSGOCount(int id);
  void DecrementSGOCount(int id);
public:
  SGOOnMapService();
  virtual ~SGOOnMapService();
  virtual SGOOnMapDbInfo Get(int id) override;
  virtual QList<SGOOnMapDbInfo> GetAll() override;
  virtual int Create(SGOOnMapDbInfo& gameObject) override;
  virtual void Update(SGOOnMapDbInfo& gameObject) override;
  virtual void Delete(int id) override;
  virtual QList<SGOOnMapDbInfo> GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string SGOName = "", std::string instanceName = "", GameObjectType gameObjectType = GameObjectType::ALL) override;
  virtual void SetPosition(int id, float x, float y, float z) override;
  virtual void SetRotation(int id, float x, float y, float z) override;
  virtual void FreezeSgo(int id) override;
  virtual void UnfreezeSgo(int id) override;
  virtual void FreezeAll() override;
  virtual void UnfreezeAll() override;
};

