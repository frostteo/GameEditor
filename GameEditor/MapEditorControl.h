#pragma once
#include <map>
#include "InputListener.h"
#include "Logger.h"
#include "Camera.h"
#include "StaticGameObject.h"

class MapEditorControl :
  public InputListener
{
public:
  static const int NOTHING_SELECTED = -1;
protected:
  Camera* m_camera;
  int* m_selectedObjectId;
  std::map<int, StaticGameObject>* m_staticGameObjectMap;
protected:
  bool RayAABBIntersect(XMFLOAT3& minPoint, XMFLOAT3& maxPoint, XMFLOAT3& position, XMFLOAT3& direction, float& result);
  void PickObject(int mouseXCoor, int mouseYCoor);
public:
  MapEditorControl();
  virtual ~MapEditorControl();
  virtual void ProcessUserInput(InputState* inputState) override;
  void SetCamera(Camera* camera) { m_camera = camera; }
  void SetSGOMap(std::map<int, StaticGameObject>* staticGameObjectMap) { m_staticGameObjectMap = staticGameObjectMap; }
  void SetSelectedObjectId(int* selectedObjectId) { m_selectedObjectId = selectedObjectId; }
};

