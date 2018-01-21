#pragma once

#include <math.h>
#include <sstream>
#include <memory>
#include "FileProcessor.h"
#include "LightininigSystem.h"

class MapEditorPreferences
{
private:
  static const std::string  m_preferencesFileName;
  std::unique_ptr<LightininigSystem> m_testLightiningSystem;

  float m_objectRotationSpeed = 1.0f;
  float m_objectMoveSpeed = 10.0f;
  float m_cameraRotationSpeed = 10.0f;
  float m_cameraZoomSpeed = 120.0f;
  float m_cameraPanSpeed = 1.0f;
  float m_angleSnap = 90.0f;
  float m_gridSnapSize = 50.f;
  bool m_snapToGrid = false;
  bool m_snapToAngle = false;

  float m_redAmbientTestLightColor = 0.15f;
  float m_greenAmbientTestLightColor = 0.15f;
  float m_blueAmbientTestLightColor = 0.15f;
  float m_redDirectTestLightColor = 1.0f;
  float m_greenDirectTestLightColor = 1.0f;
  float m_blueDirectTestLightColor = 1.0f;
  float m_xDirectTestLightDirection = 1.0f;
  float m_yDirectTestLightDirection = 0.0f;
  float m_zDirectTestLightDirection = 1.0f;

  bool m_useTestLightining = true;

  float m_redAmbientColor = 0.0f;
  float m_greenAmbientColor = 0.0f;
  float m_blueAmbientColor = 0.0f;
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

  void SetAmbientTestLightColor(float red, float green, float blue);
  void SetDirectTestLightColor(float red, float green, float blue);
  void SetDirectTestLightDirection(float x, float y, float z);

  float GetRedAmbientTestLightColor() { return m_redAmbientTestLightColor; }
  float GetGreenAmbientTestLightColor() { return m_greenAmbientTestLightColor; }
  float GetBlueAmbientTestLightColor() { return m_blueAmbientTestLightColor; }

  float GetRedDirectTestLightColor() { return m_redDirectTestLightColor; }
  float GetGreenDirectTestLightColor() { return m_greenDirectTestLightColor; }
  float GetBlueDirectTestLightColor() { return m_blueDirectTestLightColor; }

  float GetXDirectTestLightDirection() { return m_xDirectTestLightDirection; }
  float GetYDirectTestLightDirection() { return m_yDirectTestLightDirection; }
  float GetZDirectTestLightDirection() { return m_zDirectTestLightDirection; }

  void SetUseTestLightiningFlag(bool useTestLightining) { m_useTestLightining = useTestLightining; }
  bool GetUseTestLightiningFlag() { return m_useTestLightining; }

  float GetRedAmbientLightColor() { return m_redAmbientColor; }
  float GetGreenAmbientLightColor() { return m_greenAmbientColor; }
  float GetBlueAmbientLightColor() { return m_blueAmbientColor; }
  void SetAmbientLightColor(float red, float green, float blue);

  LightininigSystem* GetTestLightiningSystem() { return m_testLightiningSystem.get(); }
  MapEditorPreferences();
  virtual ~MapEditorPreferences();
};

