#pragma once
class MapEditorPreferences
{
private:
  float m_objectRotationSpeed = 1.0f;
  float m_objectMoveSpeed = 1.0f;
  float m_cameraRotationSpeed = 1.0f;
  float m_cameraZoomSpeed = 2.0f;
public:
  float GetObjectRotationSpeed() { return m_objectRotationSpeed; }
  float GetObjectMoveSpeed() { return m_objectMoveSpeed; }
  float GetCameraRotationSpeed() { return m_cameraRotationSpeed; }
  float GetCameraZoomSpeed() { return m_cameraZoomSpeed; }

  void SetObjectRotationSpeed(float speed) { if (speed > 0) m_objectRotationSpeed = speed; }
  void SetObjectMoveSpeed(float speed) { if (speed > 0) m_objectMoveSpeed = speed; }
  void SetCameraRotationSpeed(float speed) { if (speed > 0) m_cameraRotationSpeed = speed; }
  void SetCameraZoomSpeed(float speed) { if (speed > 0) m_cameraZoomSpeed = speed; }
  MapEditorPreferences();
  virtual ~MapEditorPreferences();
};

