#pragma once
#include <map>
#include <math.h>
#include "InputListener.h"
#include "Logger.h"
#include "Camera.h"
#include "StaticGameObject.h"
#include "LookAtObjectFromHelper.h"
#include "SGOOnMapTM.h"
#include "MapEditorPreferences.h"
#include <sstream>
#include <string>

class MapEditorControl :
  public InputListener
{
public:
  static const int NOTHING_SELECTED = -1;
protected:
  float CAMERA_ZOOM_COEF = 0.00833f; // Подобранно опытным путем, изменения колесика давало 120
protected:
  SGOOnMapTM* m_SGOOnMapTM;
  Camera* m_camera;
  int* m_selectedObjectId;
  std::map<int, StaticGameObject>* m_staticGameObjectMap;
  MapEditorPreferences* m_mapEditorPreferences;

  XMVECTOR m_rotateAroundPoint;
  bool m_needRecalculateRotationAroundPoint = true;
  bool m_sgoRotated;
  bool m_sgoTranslated;
  float m_timeInSecondsBetweenFrames;

  XMFLOAT3 m_accumulativePositionForSnap;
  bool m_needRecalculateAcumulativePositionForSnap = true;

  XMFLOAT3 m_accumulativeRotationForSnap;
  bool m_needRecalculateAcumulativeRotationForSnap = true;
protected:
  bool RayAABBIntersect(XMFLOAT3& minPoint, XMFLOAT3& maxPoint, XMFLOAT3& position, XMFLOAT3& direction, float& result);
  void PickObject(int mouseXCoor, int mouseYCoor);
  void RotateCamera(InputState* inputState);
  void MoveCamera(InputState* inputState);
  void RotateObject(InputState* inputState);
  void MoveObject(InputState* inputState);

  void RotateCameraAroundObject(InputState* inputState);

  XMMATRIX GetCameraMatrixRotateAroundTarget(XMVECTOR cameraPosition, XMVECTOR targetPoint, float deltaXRadians, float deltaYRadians);
  XMMATRIX GetCameraMatrixRotateAroundTarget(XMVECTOR cameraPosition, XMVECTOR targetPoint, float deltaXRadians, float deltaYRadians, XMVECTOR cameraRight);

  int GetSign(float number) { return number >= 0 ? 1 : -1; }
  float GetCorrectedWithSnapDelta(float delta, float snapSize);
  float GetCorrectedWithSnapCoord(float coord, float snapSize);
public:
  MapEditorControl(MapEditorPreferences* mapEditorPreferences, SGOOnMapTM* sgoOnMapTM, Camera* camera, std::map<int, StaticGameObject>* staticGameObjectMap);
  virtual ~MapEditorControl();
  virtual void ProcessUserInput(InputState* inputState) override;
  void SetSGOOnMapTM(SGOOnMapTM* sgoOnMapTM) { m_SGOOnMapTM = sgoOnMapTM; }
  void SetCamera(Camera* camera) { m_camera = camera; }
  void SetSGOMap(std::map<int, StaticGameObject>* staticGameObjectMap) { m_staticGameObjectMap = staticGameObjectMap; }
  void SetSelectedObjectId(int* selectedObjectId) { m_selectedObjectId = selectedObjectId; }
  void SetMapEditorPreferenses(MapEditorPreferences* mapEditorPreferences) { m_mapEditorPreferences = mapEditorPreferences; }
};

