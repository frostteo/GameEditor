#pragma once
#include <map>
#include <set>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iterator>
#include "InputListener.h"
#include "Logger.h"
#include "Camera.h"
#include "StaticGameObject.h"
#include "LookAtObjectFromHelper.h"
#include "SGOOnMapTM.h"
#include "MapEditorPreferences.h"
#include "AddOrEditSGOOnMapDialog.h"

class SGOOnMapTableWidget;

class MapEditorControl :
  public InputListener
{
public:
  static const int NOTHING_SELECTED = -1;
protected:
  SGOOnMapTableWidget* m_sgoOnMapTableWidget;

  SGOOnMapTM* m_SGOOnMapTM;
  Camera* m_camera;
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

  std::set<int>* m_selectedObjectIds;
protected:
  bool RayAABBIntersect(XMFLOAT3& minPoint, XMFLOAT3& maxPoint, XMFLOAT3& position, XMFLOAT3& direction, float& result);
  void PickObject(InputState* inputState, int mouseXCoor, int mouseYCoor);
  void RotateCamera(InputState* inputState);
  void MoveCamera(InputState* inputState);
  void RotateObjects(InputState* inputState);
  void MoveObjects(InputState* inputState);

  void RotateCameraAroundObject(InputState* inputState);

  XMMATRIX GetCameraMatrixRotateAroundTarget(XMVECTOR cameraPosition, XMVECTOR targetPoint, float deltaXRadians, float deltaYRadians);
  XMMATRIX GetCameraMatrixRotateAroundTarget(XMVECTOR cameraPosition, XMVECTOR targetPoint, float deltaXRadians, float deltaYRadians, XMVECTOR cameraRight);

  float GetCorrectedWithSnapCoord(float coord, float snapSize);
  void Clone();
  void Delete();
  XMFLOAT3 GetCenterOfSelectedObjects();
  void SaveChangedPositionsInDB();
  void SaveChangedRotationsInDB();
  void CalculateDifferenceWithPoint(std::map<int, XMFLOAT3>* differenceFromPoint, XMFLOAT3 point);
public:
  MapEditorControl(MapEditorPreferences* mapEditorPreferences, SGOOnMapTableWidget* sgoOnMapTableWidget, Camera* camera, std::map<int, StaticGameObject>* staticGameObjectMap);
  virtual ~MapEditorControl();
  virtual void ProcessUserInput(InputState* inputState) override;
  void SetSGOOnMapTM(SGOOnMapTM* sgoOnMapTM) { m_SGOOnMapTM = sgoOnMapTM; }
  void SetCamera(Camera* camera) { m_camera = camera; }
  void SetSGOMap(std::map<int, StaticGameObject>* staticGameObjectMap) { m_staticGameObjectMap = staticGameObjectMap; }
  void SetSGOOnMapTableWidget(SGOOnMapTableWidget* sgoOnMapTableWidget);
  void SetMapEditorPreferenses(MapEditorPreferences* mapEditorPreferences) { m_mapEditorPreferences = mapEditorPreferences; }
  void SetSelectedObjectIds(std::set<int>* selectedObjectIds) { m_selectedObjectIds = selectedObjectIds; }
};

