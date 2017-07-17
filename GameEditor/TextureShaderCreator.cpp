#include "TextureShaderCreator.h"


TextureShaderCreator::TextureShaderCreator()
{
  m_shaderName = "texture";
}


TextureShaderCreator::~TextureShaderCreator()
{
  
}

IShader* TextureShaderCreator::Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName)
{
  if (m_shader)
  {
    return m_shader;
  }

  m_shader = new TextureShader();
  m_shader->Initialize(m_device, m_hwnd, vertexShaderName, pixelShaderName);

  return m_shader;
}