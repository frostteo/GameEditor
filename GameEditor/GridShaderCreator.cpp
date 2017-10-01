#include "GridShaderCreator.h"


GridShaderCreator::GridShaderCreator()
{
  m_shaderName = "grid";
}


GridShaderCreator::~GridShaderCreator()
{
}

IShader* GridShaderCreator::Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName)
{
  if (m_shader)
  {
    return m_shader;
  }

  m_shader = new GridShader();
  m_shader->Initialize(m_device, m_hwnd, vertexShaderName, pixelShaderName);

  return m_shader;
}
