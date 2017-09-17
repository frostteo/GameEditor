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
public:
  StaticGOService();
  virtual ~StaticGOService();
  virtual QList<StaticGameObject> GetStaticGameObjects() override;
  virtual void CreateStaticGameObject(StaticGameObject& gameObject) override;
  virtual void UpdateStaticGameObject(StaticGameObject& gameObject) override;
  virtual void DeleteStaticGameObject(int id) override;
  virtual QList<StaticGameObject> GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string name = "", std::string model = "", std::string material = "") override;
};

