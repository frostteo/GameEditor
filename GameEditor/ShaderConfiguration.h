#pragma once
#include <string>
#include <map>

class ShaderConfiguration
{
private:
  typedef std::map<std::string, std::string, std::less<>> shaderNameMap;
private:
  shaderNameMap m_shaderNameMap;

  std::wstring m_pathToVertexShader;
  std::wstring m_pathToPixelShader;
  std::wstring m_shaderNameParam = L"[shadername]";
public:
  ShaderConfiguration();
  virtual ~ShaderConfiguration();
  void Configure(); //TODO FHolod: Later can be loaded from file
  std::wstring GetVertexShaderFileName(const std::string& shaderName);
  std::wstring GetPixelShaderFileName(const std::string& shaderName);
  const std::string& GetConfiguredShaderName(const std::string& shaderName);
};

