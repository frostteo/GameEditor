#pragma once
#include <d3d11.h>
#include <string>
#include "IShader.h"

class IShaderCreator
{
protected:
  std::string m_shaderName;
  ID3D11Device* m_device;
  HWND m_hwnd;
  IShader* m_shader;
public:
  IShaderCreator() { m_shader = nullptr; }
  IShaderCreator* Initialize(ID3D11Device* device, HWND hwnd) { m_device = device; m_hwnd = hwnd; return this; }
  virtual ~IShaderCreator();
  bool CanCreate(const std::string& shaderName) { return shaderName == m_shaderName; }
  virtual IShader* Get(const std::wstring& vertexShaderName, const std::wstring& geometricShaderName, const std::wstring& hullShaderName, const std::wstring& domainShaderName, const std::wstring& pixelShaderName) {
    return nullptr;
  }
};

