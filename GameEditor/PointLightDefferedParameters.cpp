#include "PointLightDefferedParameters.h"

const std::string PointLightDefferedParameters::pointLightDefferedParametersType = "pointLightDefferedParameters";

PointLightDefferedParameters::PointLightDefferedParameters() : IMaterial(pointLightDefferedParametersType)
{
}


PointLightDefferedParameters::~PointLightDefferedParameters()
{
}

void PointLightDefferedParameters::SetPerspectiveValues(XMMATRIX projectionMatrix)
{
  XMFLOAT4X4 readableProjectionMatrix;
  XMFLOAT4 perspectiveValuesReadable;

  XMStoreFloat4x4(&readableProjectionMatrix, projectionMatrix);
  perspectiveValuesReadable.x = 1.0f / readableProjectionMatrix._11;
  perspectiveValuesReadable.y = 1.0f / readableProjectionMatrix._22;
  perspectiveValuesReadable.z = readableProjectionMatrix._43;
  perspectiveValuesReadable.w = -readableProjectionMatrix._33;

  m_perspectiveValues = XMLoadFloat4(&perspectiveValuesReadable);
}