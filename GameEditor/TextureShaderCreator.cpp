#include "TextureShaderCreator.h"


TextureShaderCreator::TextureShaderCreator(ID3D11Device* device, HWND hwnd) : IShaderCreator(device, hwnd)
{
  m_shaderName = "texture";
  m_shader = nullptr;
}


TextureShaderCreator::~TextureShaderCreator()
{
  if (m_shader) {
    delete m_shader;
    m_shader = nullptr;
  }
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