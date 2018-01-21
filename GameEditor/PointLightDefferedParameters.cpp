#include "PointLightDefferedParameters.h"

const std::string PointLightDefferedParameters::pointLightDefferedParametersType = "pointLightDefferedParameters";

PointLightDefferedParameters::PointLightDefferedParameters() : IMaterial(pointLightDefferedParametersType)
{
}


PointLightDefferedParameters::~PointLightDefferedParameters()
{
}

void PointLightDefferedParameters::SetScreenWidth(float width)
{
  if (width <= 0)
    RUNTIME_ERROR("Width cannot be less or equal zero");

  m_screenWidth = width;
}

void PointLightDefferedParameters::SetScreenHeight(float height)
{
  if (height <= 0)
    RUNTIME_ERROR("Height cannot be less or equal zero");

  m_screenHeight = height;
}