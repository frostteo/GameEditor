#pragma once

#include <algorithm>
#include <initializer_list>
#include <math.h>
#include "GameObject.h"

class PointLight :
  public GameObject
{
protected:
  float m_linerarAttenuation;
  float m_quadraticAttenuation;
  XMFLOAT3 m_color;
  float m_radius = 0;
public:
  PointLight();
  void Initialize(float linearAttenuation, float quadraticAttenuation, XMFLOAT3 position, XMFLOAT3 color, GameObject* parent);
  void SetAttenuation(float linearAttenuation, float quadraticAttenuation);
  float GetLinearAttenuation() { return m_linerarAttenuation; }
  float GetQuadraticAttenuation() { return m_quadraticAttenuation; }
  XMFLOAT3 GetColor() { return m_color; }
  void SetColor(XMFLOAT3 color) { m_color = color; }
  float GetRadius() { return m_radius; }
  virtual ~PointLight();
};

