#pragma once

#include "IShaderCreator.h"
#include "GridShader.h"

class GridShaderCreator :
  public IShaderCreator
{
public:
  GridShaderCreator();
  virtual ~GridShaderCreator();
  virtual IShader* Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName) override;
};

