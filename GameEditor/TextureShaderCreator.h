#pragma once

#include "TextureShader.h"
#include "IShaderCreator.h"
#include "ShaderConfiguration.h"

class TextureShaderCreator :
  public IShaderCreator
{
public:
  TextureShaderCreator();
  virtual ~TextureShaderCreator();
  virtual IShader* Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName) override;
};

