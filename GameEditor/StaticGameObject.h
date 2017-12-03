#pragma once
#include "GameObject.h"
#include "Model.h"
#include "DrawableBoundingBox.h"

class StaticGameObject :
  public GameObject
{
private:
  Model* m_model;
  BoundingBox m_bbInWorldCoord;
  DrawableBoundingBox m_drawableBoundingBox;
public:
  int uniqueId;

  int modelId;
  bool isFrozen;
protected:
  void RebuildBBInWorldCoord();
public:
  StaticGameObject();
  virtual ~StaticGameObject();
  Model* GetModel() { return m_model; }
  void SetModel(Model* model);
  BoundingBox* GetBBInWorldCoords();
  DrawableBoundingBox* GetDrawableBoundingBox() { return &m_drawableBoundingBox; }
};

