#pragma once
#include "IMaterial.h"
#include "Logger.h"

class PointLightDefferedParameters :
  public IMaterial
{
private:
  float m_screenWidth;
  float m_screenHeight;
public:
  static const std::string pointLightDefferedParametersType;
public:
  PointLightDefferedParameters();
  virtual ~PointLightDefferedParameters();
  virtual const std::string& GetType() override { return PointLightDefferedParameters::pointLightDefferedParametersType; }
  float GetScreenWidth() { return m_screenWidth; }
  float GetScreenHeight() { return m_screenHeight; }
  void SetScreenWidth(float width);
  void SetScreenHeight(float height);
};

