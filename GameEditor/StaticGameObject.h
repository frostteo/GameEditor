#pragma once
#include "GameObject.h"

class Model;

class StaticGameObject :
  public GameObject
{
private:
  Model* m_model = nullptr;
public:
  int uniqueId = 0;

  int dbInfoId = 0;
  bool isFrozen = false;
  bool castShadows = true;
protected:
  virtual void RebuildBBInWorldCoord() const override;
public:
  StaticGameObject() = default;
  virtual ~StaticGameObject() = default;
  const Model* GetModel() const { return m_model; }
  void SetModel(Model* model);
};

