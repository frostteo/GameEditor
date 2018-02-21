#pragma once

#include <algorithm>
#include <initializer_list>
#include <math.h>
#include "GameObject.h"

class PointLight :
  public GameObject
{
protected:
  static const float SHADOW_NEAR_PLANE;

  float m_linerarAttenuation;
  float m_quadraticAttenuation;
  XMFLOAT3 m_color;
  float m_radius = 0;

  XMMATRIX m_cubeViewProjection[6];
  XMFLOAT2 m_lightPerspectiveValues;
  XMFLOAT3 m_oldWorldPosition;
protected:
  void RebuildPerspectiveValues();
  void RebuildCubeViewProjection(XMFLOAT3 worldPosition);
public:
  bool castShadows = false;
public:
  PointLight();
  void virtual SetPosition(float x, float y, float z) override;
  void Initialize(float linearAttenuation, float quadraticAttenuation, XMFLOAT3 position, XMFLOAT3 color, GameObject* parent, bool castShadows = false);
  void SetAttenuation(float linearAttenuation, float quadraticAttenuation);
  float GetLinearAttenuation() { return m_linerarAttenuation; }
  float GetQuadraticAttenuation() { return m_quadraticAttenuation; }
  XMFLOAT3 GetColor() { return m_color; }
  void SetColor(XMFLOAT3 color) { m_color = color; }
  float GetRadius() { return m_radius; }
  virtual ~PointLight();

  XMMATRIX* GetCubeViewProjection();
  XMFLOAT2 GetLightPerspectiveValues();
};

