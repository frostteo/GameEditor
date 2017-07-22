#pragma once

#include "IShaderCreator.h"
#include "BumpSpecSingleLightSh.h"

class BumpSpecSingleLightShCreator :
  public IShaderCreator
{
public:
  BumpSpecSingleLightShCreator();
  virtual ~BumpSpecSingleLightShCreator();
  virtual IShader* Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName) override;
};

