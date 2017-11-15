#pragma once
#include <map>
#include <math.h>
#include "InputListener.h"
#include "Logger.h"
#include "Camera.h"
#include "StaticGameObject.h"
#include "LookAtObjectFromHelper.h"

class MapEditorControl :
  public InputListener
{
public:
  static const int NOTHING_SELECTED = -1;
protected:
  float CAMERA_ROTATION_COEF = 0.1f; //TODO FHolod: later will be depends on render preferences
protected:
  Camera* m_camera;
  int* m_selectedObjectId;
  std::map<int, StaticGameObject>* m_staticGameObjectMap;

  XMVECTOR m_rotateAroundPoint;
  bool m_needRecalculateRotationAroundPoint = true;
protected:
  bool RayAABBIntersect(XMFLOAT3& minPoint, XMFLOAT3& maxPoint, XMFLOAT3& position, XMFLOAT3& direction, float& result);
  void PickObject(int mouseXCoor, int mouseYCoor);
  void RotateCamera(InputState* inputState);
  void MoveCamera(InputState* inputState);
  void RotateObject(InputState* inputState);
  void MoveObject(InputState* inputState);

  void RotateCameraAroundObject(InputState* inputState);

  XMMATRIX GetCameraMatrixRotateAroundTarget(XMVECTOR cameraPosition, XMVECTOR targetPoint, float deltaX, float deltaY);
  XMMATRIX GetCameraMatrixRotateAroundTarget(XMVECTOR cameraPosition, XMVECTOR targetPoint, float deltaX, float deltaY, XMVECTOR cameraRight);
public:
  MapEditorControl(Camera* camera, std::map<int, StaticGameObject>* staticGameObjectMap);
  virtual ~MapEditorControl();
  virtual void ProcessUserInput(InputState* inputState) override;
  void SetCamera(Camera* camera) { m_camera = camera; }
  void SetSGOMap(std::map<int, StaticGameObject>* staticGameObjectMap) { m_staticGameObjectMap = staticGameObjectMap; }
  void SetSelectedObjectId(int* selectedObjectId) { m_selectedObjectId = selectedObjectId; }
};

