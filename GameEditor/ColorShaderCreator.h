#pragma once

#include "IShaderCreator.h"
#include "ShaderConfiguration.h"
#include "ColorShader.h"

class ColorShaderCreator :
  public IShaderCreator
{
public:
  ColorShaderCreator();
  virtual ~ColorShaderCreator();
  virtual IShader* Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName) override;
};

