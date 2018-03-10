#pragma once

#include "GameObject.h"
#include "CameraFrustrum.h"

class Logger;

using namespace DirectX;

class Camera : public GameObject
{
private:
  float m_screenWidth;
  float m_screenHeight;
  float m_screenNear;
  float m_screenDepth;
  float m_fieldOfView;
  XMMATRIX m_orthoMatrix;
  XMMATRIX m_projectionMatrix;

  CameraFrustrum m_cameraFrustrum;
  bool m_needRebuildFrustrum = true;
protected:
  virtual void RebuildWorldMatrix() override;
  virtual void RebuildBBInWorldCoord() override;
public:
  Camera();
  void Initialize(float screenWidth, float screenHeight, float screenNear, float screenDepth, float fieldOfView = XM_PIDIV4);
  virtual ~Camera();
  void GetViewMatrix(XMMATRIX& viewMatrix);
  void GetOrthoMatrix(XMMATRIX& orthoMatrix);
  void GetProjectionMatrix(XMMATRIX& projectionMatrix);
  float GetScreenWidth() { return m_screenWidth; }
  float GetScreenHeight() { return m_screenHeight; }
  float GetFieldOfView() { return m_fieldOfView; }

  bool NeedRebuildFrustrum() const { return this->m_needRebuildFrustrum; }
  CameraFrustrum* GetCameraFrustrum();
};

