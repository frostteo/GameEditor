#pragma once
#include "GameObject.h"
#include "Model.h"

class StaticGameObject :
  public GameObject
{
private:
  Model* m_model;
public:
  int m_SGODbInfoId;
public:
  StaticGameObject();
  virtual ~StaticGameObject();
  Model* GetModel() { return m_model; }
  void SetModel(Model* model) { m_model = model; }
};

