#include "BumpSpecSingleLightShCreator.h"


BumpSpecSingleLightShCreator::BumpSpecSingleLightShCreator()
{
  m_shaderName = "bumpSpec";
}


BumpSpecSingleLightShCreator::~BumpSpecSingleLightShCreator()
{
}

IShader* BumpSpecSingleLightShCreator::Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName)
{
  if (m_shader)
  {
    return m_shader;
  }

  m_shader = new BumpSpecSingleLightSh();
  m_shader->Initialize(m_device, m_hwnd, vertexShaderName, pixelShaderName);

  return m_shader;
}