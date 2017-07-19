#include "SpecularSingleDirLightShaderCreator.h"


SpecularSingleDirLightShaderCreator::SpecularSingleDirLightShaderCreator()
{
  m_shaderName = "specularSingleDirLight";
}


SpecularSingleDirLightShaderCreator::~SpecularSingleDirLightShaderCreator()
{
}

IShader* SpecularSingleDirLightShaderCreator::Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName)
{
  if (m_shader)
  {
    return m_shader;
  }

  m_shader = new SpecularSingleDirLightShader();
  m_shader->Initialize(m_device, m_hwnd, vertexShaderName, pixelShaderName);

  return m_shader;
}
