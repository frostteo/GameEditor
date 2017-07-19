#pragma once

#include "IShaderCreator.h"
#include "ShaderConfiguration.h"
#include "SpecularSingleDirLightShader.h"

class SpecularSingleDirLightShaderCreator :
  public IShaderCreator
{
public:
  SpecularSingleDirLightShaderCreator();
  virtual ~SpecularSingleDirLightShaderCreator();
  virtual IShader* Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName) override;
};

