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
  mutable bool m_needRebuildFrustrum = true;
protected:
  virtual void RebuildWorldMatrix() const override;
  virtual void RebuildBBInWorldCoord() const override;
public:
  Camera() = default;
  virtual ~Camera() = default;

  void Initialize(float screenWidth, float screenHeight, float screenNear, float screenDepth, float fieldOfView = XM_PIDIV4);
  void GetViewMatrix(XMMATRIX& viewMatrix) const;
  void GetOrthoMatrix(XMMATRIX& orthoMatrix) const;
  void GetProjectionMatrix(XMMATRIX& projectionMatrix) const;
  float GetScreenWidth() const { return m_screenWidth; }
  float GetScreenHeight() const { return m_screenHeight; }
  float GetFieldOfView() const { return m_fieldOfView; }

  bool NeedRebuildFrustrum() const { return this->m_needRebuildFrustrum; }
  const CameraFrustrum* GetCameraFrustrum();
};

