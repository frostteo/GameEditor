#pragma once

#include <vector>
#include <algorithm>
#include "IStaticGOService.h"
#include "BLLDependencyResolver.h"
#include "IUnitOfWork.h"
#include "Utils.h"

class StaticGOService
  : public IStaticGOService
{
protected:
  IUnitOfWork* m_unitOfWork;
  SGOMetadata m_metadata;
public:
  StaticGOService();
  virtual ~StaticGOService();
  virtual StaticGameObjectDbInfo GetStaticGameObject(int id) override;
  virtual QList<StaticGameObjectDbInfo> GetStaticGameObjects() override;
  virtual int CreateStaticGameObject(StaticGameObjectDbInfo& gameObject) override;
  virtual void UpdateStaticGameObject(StaticGameObjectDbInfo& gameObject) override;
  virtual void DeleteStaticGameObject(int id) override;
  virtual QList<StaticGameObjectDbInfo> GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string name = "", std::string model = "") override;
};

