#pragma once
#include "IMaterial.h"

class Logger;

class PointLightDefferedParameters :
  public IMaterial
{
private:
  XMVECTOR m_perspectiveValues;
  XMMATRIX m_viewMatrixInv;
public:
  static const std::string pointLightDefferedParametersType;
public:
  PointLightDefferedParameters();
  virtual ~PointLightDefferedParameters();
  virtual const std::string& GetType() override { return PointLightDefferedParameters::pointLightDefferedParametersType; }
  XMVECTOR GetPerspectiveValues() { return m_perspectiveValues; }
  XMMATRIX GetViewMatrixInverse() { return m_viewMatrixInv; }
  void SetPerspectiveValues(XMMATRIX projectionMatrix);
  void SetViewMatrixInverse(XMMATRIX viewMatrixInv) { m_viewMatrixInv = viewMatrixInv; }
};

