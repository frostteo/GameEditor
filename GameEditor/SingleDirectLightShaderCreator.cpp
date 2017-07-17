#include "SingleDirectLightShaderCreator.h"


SingleDirectLightShaderCreator::SingleDirectLightShaderCreator()
{
  m_shaderName = "singleDirectLight";
}


SingleDirectLightShaderCreator::~SingleDirectLightShaderCreator()
{
 
}


IShader* SingleDirectLightShaderCreator::Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName)
{
  if (m_shader)
  {
    return m_shader;
  }

  m_shader = new SingleDirectLightShader();
  m_shader->Initialize(m_device, m_hwnd, vertexShaderName, pixelShaderName);

  return m_shader;
}