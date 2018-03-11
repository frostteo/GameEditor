#pragma once
#include "GameObject.h"
#include "DrawableBoundingBox.h"

class Model;

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
  virtual void RebuildBBInWorldCoord() const override;
public:
  StaticGameObject() = default;
  virtual ~StaticGameObject() = default;
  const Model* GetModel() const { return m_model; }
  void SetModel(Model* model);
  DrawableBoundingBox* GetDrawableBoundingBox() { return &m_drawableBoundingBox; }
};

