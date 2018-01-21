#pragma once

#include <string>
#include "IShaderCreator.h"

template <class Shader, const std::string& ShaderName>
class TemplateShaderCreator :
  public IShaderCreator
{
public:
  TemplateShaderCreator();
  virtual ~TemplateShaderCreator();
  virtual IShader* Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName) override;
};

template <class Shader, const std::string& ShaderName>
TemplateShaderCreator<Shader, ShaderName>::TemplateShaderCreator()
{
  m_shaderName = ShaderName;
}

template <class Shader, const std::string& ShaderName>
TemplateShaderCreator<Shader, ShaderName>::~TemplateShaderCreator()
{
}

template <class Shader, const std::string& ShaderName>
IShader* TemplateShaderCreator<Shader, ShaderName>::Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName)
{
  if (m_shader)
  {
    return m_shader;
  }

  m_shader = new Shader();
  m_shader->Initialize(m_device, m_hwnd, vertexShaderName, pixelShaderName);

  return m_shader;
}

