#pragma once

#include <vector>
#include <algorithm>
#include "IStaticGOService.h"
#include "BLLDependencyResolver.h"
#include "IUnitOfWork.h"

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
};

