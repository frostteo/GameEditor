#include "BumpSpecMapShaderCreator.h"


BumpSpecMapShaderCreator::BumpSpecMapShaderCreator()
{
  m_shaderName = "bumpSpecMap";
}


BumpSpecMapShaderCreator::~BumpSpecMapShaderCreator()
{
}

IShader* BumpSpecMapShaderCreator::Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName)
{
  if (m_shader)
  {
    return m_shader;
  }

  m_shader = new BumpSpecMapShader();
  m_shader->Initialize(m_device, m_hwnd, vertexShaderName, pixelShaderName);

  return m_shader;
}
