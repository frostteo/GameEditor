#pragma once
#include "GameObject.h"
#include "Model.h"
#include "DrawableBoundingBox.h"

class StaticGameObject :
  public GameObject
{
private:
  Model* m_model;
  DrawableBoundingBox m_drawableBoundingBox;
public:
  int uniqueId;

  int dbInfoId;
  bool isFrozen;
  bool castShadows = true;
protected:
  virtual void RebuildBBInWorldCoord() override;
public:
  StaticGameObject();
  virtual ~StaticGameObject();
  Model* GetModel() { return m_model; }
  void SetModel(Model* model);
  DrawableBoundingBox* GetDrawableBoundingBox() { return &m_drawableBoundingBox; }
};

