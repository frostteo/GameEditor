#pragma once

#include "GameObject.h"

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
};

