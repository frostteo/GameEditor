#pragma once
#include <string>
#include <map>

class ShaderConfiguration
{
private:
  struct ShaderNamesSet
  {
    std::string configuredShaderName;
    std::string vsShaderName;
    std::string gsShaderName;
    std::string hlShaderName;
    std::string dmShaderName;
    std::string psShaderName;
  };
private:
  typedef std::map<std::string, ShaderNamesSet, std::less<>> shaderNameMap;
private:
  shaderNameMap m_shaderNameMap;

  std::wstring m_pathToVertexShader;
  std::wstring m_pathToGeometricShader;
  std::wstring m_pathToHullShader;
  std::wstring m_pathToDomainShader;
  std::wstring m_pathToPixelShader;

  std::wstring m_shaderNameParam = L"[shadername]";
protected:
  std::wstring GetShaderFileName(const std::string& shaderName, std::wstring& m_pathToShaderType);
public:
  ShaderConfiguration();
  virtual ~ShaderConfiguration();
  void ConfigureForwardRenderer();
  void ConfigureDefferedRenderer();

  bool IsThisShaderInMap(const std::string& shaderName);

  std::string GetConfiguredShaderName(const std::string& shaderName) { return m_shaderNameMap[shaderName].configuredShaderName; }
  std::wstring GetVertexShaderFileName(const std::string& shaderName);
  std::wstring GetGeometricShaderFileName(const std::string& shaderName);
  std::wstring GetHullShaderFileName(const std::string& shaderName);
  std::wstring GetDomainShaderFileName(const std::string& shaderName);
  std::wstring GetPixelShaderFileName(const std::string& shaderName);
};

