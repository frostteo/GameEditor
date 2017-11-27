#pragma once
#include "GameObject.h"
#include "Model.h"

class StaticGameObject :
  public GameObject
{
private:
  Model* m_model;
  BoundingBox m_bbInWorldCoord;
public:
  int m_SGODbInfoId;
protected:
  void RebuildBBInWorldCoord();
public:
  StaticGameObject();
  virtual ~StaticGameObject();
  Model* GetModel() { return m_model; }
  void SetModel(Model* model);
  BoundingBox* GetBBInWorldCoords();
};

