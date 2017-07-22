#pragma once
#include "IShaderCreator.h"
#include "BumpSingleDirLightShader.h"

class BumpSingleDirLightShaderCreator :
  public IShaderCreator
{
public:
  BumpSingleDirLightShaderCreator();
  virtual ~BumpSingleDirLightShaderCreator();
  virtual IShader* Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName) override;
};

