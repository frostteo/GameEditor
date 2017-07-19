#pragma once

#include "IShaderCreator.h"
#include "SingleDirectLightShader.h"

class SingleDirectLightShaderCreator :
  public IShaderCreator
{
public:
  SingleDirectLightShaderCreator();
  virtual ~SingleDirectLightShaderCreator();
  virtual IShader* Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName) override;
};

