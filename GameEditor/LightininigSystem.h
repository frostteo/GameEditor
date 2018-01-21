#pragma once

#include <directxmath.h>
#include <vector>
#include "PointLight.h"

using namespace DirectX;

class LightininigSystem
{
protected:
  XMVECTOR m_ambientColor;
  XMVECTOR m_directLightColor;
  XMFLOAT3 m_directLightDirection;
  std::vector<PointLight*> m_pointLights;
public:
  void SetAmbientColor(float red, float green, float blue, float alpha) { m_ambientColor = XMVectorSet(red, green, blue, alpha); }
  void SetDirectLightColor(float red, float green, float blue, float alpha) { m_directLightColor = XMVectorSet(red, green, blue, alpha); }
  void SetDirectLightDirection(float x, float y, float z)  { m_directLightDirection = XMFLOAT3(x, y, z); }
  XMVECTOR& GetAmbientColor() { return m_ambientColor; }
  XMVECTOR& GetDirectLightColor() { return m_directLightColor; }
  XMFLOAT3& GetDirectLightDirection() { return m_directLightDirection; }
  void AddPointLight(PointLight* pointLight) { m_pointLights.push_back(pointLight); }
  std::vector<PointLight*>* GetPointLights() { return &m_pointLights; }
  void ClearLights() { m_pointLights.clear(); }
  LightininigSystem();
  virtual ~LightininigSystem();
};

