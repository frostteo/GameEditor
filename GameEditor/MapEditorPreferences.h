#pragma once

#include <math.h>
#include <sstream>
#include "FileProcessor.h"

class MapEditorPreferences
{
private:
  static const std::string  m_preferencesFileName;

  float m_objectRotationSpeed = 1.0f;
  float m_objectMoveSpeed = 10.0f;
  float m_cameraRotationSpeed = 10.0f;
  float m_cameraZoomSpeed = 120.0f;
  float m_cameraPanSpeed = 1.0f;
  float m_angleSnap = 90.0f;
  float m_gridSnapSize = 50.f;
  bool m_snapToGrid = false;
  bool m_snapToAngle = false;

protected:
  void ReadPreferencesFromStr(std::string& str);
public:
  float GetObjectRotationSpeed() { return m_objectRotationSpeed; }
  float GetObjectMoveSpeed() { return m_objectMoveSpeed; }
  float GetCameraRotationSpeed() { return m_cameraRotationSpeed; }
  float GetCameraZoomSpeed() { return m_cameraZoomSpeed; }
  float GetCameraPanSpeed() { return m_cameraPanSpeed; }
  float GetGridSnapSize() { return m_gridSnapSize; }
  float GetAngleSnap() { return m_angleSnap; }
  bool GetSnapToGridState() { return m_snapToGrid; }
  bool GetSnapToAngleState() { return m_snapToAngle; }
 
  void SetObjectRotationSpeed(float speed) { if (speed > 0) m_objectRotationSpeed = speed; }
  void SetObjectMoveSpeed(float speed) { if (speed > 0) m_objectMoveSpeed = speed; }
  void SetCameraRotationSpeed(float speed) { if (speed > 0) m_cameraRotationSpeed = speed; }
  void SetCameraZoomSpeed(float speed) { if (speed > 0) m_cameraZoomSpeed = speed; }
  void SetCameraPanSpeed(float speed) { if (speed > 0) m_cameraPanSpeed = speed; }
  void SetAngleSnap(float angle);
  void SetGridSnapSize(float size);
  void SetSnapToGridState(bool useGrid) { m_snapToGrid = useGrid; }
  void SetSnapToAngleState(bool useAngle) { m_snapToAngle = useAngle; }

  MapEditorPreferences();
  virtual ~MapEditorPreferences();
};

