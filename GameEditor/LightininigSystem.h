#pragma once

#include <directxmath.h>
using namespace DirectX;

class LightininigSystem
{
protected:
  XMVECTOR m_ambientColor;
  XMVECTOR m_directLightColor;
  XMFLOAT3 m_directLightDirection;
public:
  void SetAmbientColor(float red, float green, float blue, float alpha) { m_ambientColor = XMVectorSet(red, green, blue, alpha); }
  void SetDirectLightColor(float red, float green, float blue, float alpha) { m_directLightColor = XMVectorSet(red, green, blue, alpha); }
  void SetDirectLightDirection(float x, float y, float z)  { m_directLightDirection = XMFLOAT3(x, y, z); }
  XMVECTOR& GetAmbientColor() { return m_ambientColor; }
  XMVECTOR& GetDirectLightColor() { return m_directLightColor; }
  XMFLOAT3& GetDirectLightDirection() { return m_directLightDirection; }
  LightininigSystem();
  virtual ~LightininigSystem();
};

