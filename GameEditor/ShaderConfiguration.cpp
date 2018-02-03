#include "ShaderConfiguration.h"


ShaderConfiguration::ShaderConfiguration()
{
  m_pathToVertexShader = L"../GameEditor/shaders/[shadername].vs";
  m_pathToHullShader = L"../GameEditor/shaders/[shadername].hs";
  m_pathToDomainShader = L"../GameEditor/shaders/[shadername].ds";
  m_pathToPixelShader = L"../GameEditor/shaders/[shadername].ps";
}


ShaderConfiguration::~ShaderConfiguration()
{
}

void ShaderConfiguration::ConfigureForwardRenderer()
{
  m_shaderNameMap.clear();
  m_shaderNameMap.insert(shaderNameMap::value_type("color", { "colorSingleDirLight", "colorSingleDirLight", "colorSingleDirLight", "colorSingleDirLight", "colorSingleDirLight" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("texture", { "texture", "texture", "texture", "texture", "texture" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("specular", { "specularSingleDirLight", "specularSingleDirLight", "specularSingleDirLight", "specularSingleDirLight", "specularSingleDirLight" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("bump", { "bump", "bump", "bump", "bump", "bump" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("bumpSpec", { "bumpSpec", "bumpSpec", "bumpSpec", "bumpSpec", "bumpSpec" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("bumpSpecMap", { "bumpSpecMap", "bumpSpecMap", "bumpSpecMap", "bumpSpecMap", "bumpSpecMap" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("grid", { "grid", "grid", "grid", "grid", "grid" }));
}

void ShaderConfiguration::ConfigureDefferedRenderer()
{
  m_shaderNameMap.clear();
  m_shaderNameMap.insert(shaderNameMap::value_type("color", { "colorDeffered", "colorDeffered", "colorDeffered", "colorDeffered", "colorDeffered" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("texture", { "textureDeffered", "textureDeffered", "textureDeffered", "textureDeffered", "textureDeffered" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("specular", { "specularDeffered", "specularDeffered", "specularDeffered", "specularDeffered", "specularDeffered" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("bump", { "bumpDeffered", "bumpDeffered", "bumpDeffered", "bumpDeffered", "bumpDeffered" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("bumpSpec", { "bumpSpecDeffered", "bumpSpecDeffered", "bumpSpecDeffered", "bumpSpecDeffered", "bumpSpecDeffered" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("bumpSpecMap", { "bumpSpecMapDeffered", "bumpSpecMapDeffered", "bumpSpecMapDeffered", "bumpSpecMapDeffered", "bumpSpecMapDeffered" }));

  m_shaderNameMap.insert(shaderNameMap::value_type("grid", { "grid", "grid", "grid", "grid", "grid" }));

  m_shaderNameMap.insert(shaderNameMap::value_type("ambientDeffered", { "ambientDeffered", "ambientDeffered", "ambientDeffered", "ambientDeffered", "ambientDeffered" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("depthBuffer", { "depthBuffer", "depthBuffer", "depthBuffer", "depthBuffer", "depthBuffer" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("pointLightDeffered", { "pointLightDeffered", "pointLightDeffered", "pointLightDeffered", "pointLightDeffered", "pointLightDeffered" }));
  m_shaderNameMap.insert(shaderNameMap::value_type("pointLightTesselated", { "pointLightTesselated", "pointLightDefferedTessellated", "pointLightDefferedTessellated", "pointLightDefferedTessellated", "pointLightDeffered" }));
}

bool ShaderConfiguration::IsThisShaderInMap(const std::string& shaderName)
{
  return m_shaderNameMap.count(shaderName);
}

std::wstring ShaderConfiguration::GetShaderFileName(const std::string& shaderName, std::wstring& m_pathToShaderType)
{
  std::wstring shaderNameUnicode(shaderName.begin(), shaderName.end());
  std::wstring templatePath = m_pathToShaderType;
  size_t firstPos = templatePath.find(m_shaderNameParam);
  templatePath.replace(firstPos, m_shaderNameParam.length(), shaderNameUnicode);
  return templatePath;
}

std::wstring ShaderConfiguration::GetVertexShaderFileName(const std::string& shaderName)
{
  return GetShaderFileName(m_shaderNameMap[shaderName].vsShaderName, m_pathToVertexShader);
}

std::wstring ShaderConfiguration::GetHullShaderFileName(const std::string& shaderName)
{
  return GetShaderFileName(m_shaderNameMap[shaderName].hlShaderName, m_pathToHullShader);
}

std::wstring ShaderConfiguration::GetDomainShaderFileName(const std::string& shaderName)
{
  return GetShaderFileName(m_shaderNameMap[shaderName].dmShaderName, m_pathToDomainShader);
}

std::wstring ShaderConfiguration::GetPixelShaderFileName(const std::string& shaderName)
{
  return GetShaderFileName(m_shaderNameMap[shaderName].psShaderName, m_pathToPixelShader);
}