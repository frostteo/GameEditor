#include "ColorShaderCreator.h"


ColorShaderCreator::ColorShaderCreator()
{
  m_shaderName = "colorSingleDirLight";
}


ColorShaderCreator::~ColorShaderCreator()
{
}

IShader* ColorShaderCreator::Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName)
{
  if (m_shader)
  {
    return m_shader;
  }

  m_shader = new ColorShader();
  m_shader->Initialize(m_device, m_hwnd, vertexShaderName, pixelShaderName);

  return m_shader;
}