#include "LightininigSystem.h"
#include "Logger.h"
#include "PointLight.h"

LightininigSystem::LightininigSystem()
{
}

LightininigSystem::~LightininigSystem()
{
}

void LightininigSystem::AddPointLight(PointLight* pointLight)
{
  if (pointLight->castShadows)
    m_pointLightsCastShadows.push_back(pointLight);

  else
    m_pointLightsNonCastShadows.push_back(pointLight);
}

void LightininigSystem::ClearLights()
{
  m_pointLightsNonCastShadows.clear();
  m_pointLightsCastShadows.clear();
}

void LightininigSystem::SetPointLightToRenderSelector(bool castShadow, int index)
{
  if (index < 0 || castShadow && index >= m_pointLightsCastShadows.size() || !castShadow && index >= m_pointLightsNonCastShadows.size())
  {
    RUNTIME_ERROR("It is impossible to choose this point light to render index: out of range");
  }

  m_castShadowRenderFlag = castShadow;
  m_pointLightToRenderIndex = index;
}

PointLight* LightininigSystem::GetPointLightToRender() const
{
  if (m_castShadowRenderFlag)
    return m_pointLightsCastShadows[m_pointLightToRenderIndex];
  else
    return m_pointLightsNonCastShadows[m_pointLightToRenderIndex];
}