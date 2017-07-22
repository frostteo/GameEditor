#pragma once

#include "IShaderCreator.h"
#include "BumpSpecMapShader.h"

class BumpSpecMapShaderCreator :
  public IShaderCreator
{
public:
  BumpSpecMapShaderCreator();
  virtual ~BumpSpecMapShaderCreator();
  virtual IShader* Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName) override;
};

