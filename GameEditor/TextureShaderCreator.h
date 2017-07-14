#pragma once

#include "TextureShader.h"
#include "IShaderCreator.h"
#include "ShaderConfiguration.h"

class TextureShaderCreator :
  public IShaderCreator
{
private:
  TextureShader* m_shader;
public:
  TextureShaderCreator(ID3D11Device* device, HWND hwnd);
  virtual ~TextureShaderCreator();
  virtual IShader* Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName) override;
};

