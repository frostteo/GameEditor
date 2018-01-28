#include "ShaderConfiguration.h"


ShaderConfiguration::ShaderConfiguration()
{

}


ShaderConfiguration::~ShaderConfiguration()
{
}

void ShaderConfiguration::ConfigureForwardRenderer()
{
  m_pathToVertexShader = L"../GameEditor/shaders/[shadername].vs";
  m_pathToPixelShader = L"../GameEditor/shaders/[shadername].ps";

  m_shaderNameMap.clear();
  m_shaderNameMap.insert(shaderNameMap::value_type("color", "colorSingleDirLight"));
  m_shaderNameMap.insert(shaderNameMap::value_type("texture", "texture"));
  m_shaderNameMap.insert(shaderNameMap::value_type("specular", "specularSingleDirLight"));
  m_shaderNameMap.insert(shaderNameMap::value_type("bump", "bump"));
  m_shaderNameMap.insert(shaderNameMap::value_type("bumpSpec", "bumpSpec"));
  m_shaderNameMap.insert(shaderNameMap::value_type("bumpSpecMap", "bumpSpecMap"));
  m_shaderNameMap.insert(shaderNameMap::value_type("grid", "grid"));
}

void ShaderConfiguration::ConfigureDefferedRenderer()
{
  m_pathToVertexShader = L"../GameEditor/shaders/[shadername].vs";
  m_pathToPixelShader = L"../GameEditor/shaders/[shadername].ps";

  m_shaderNameMap.clear();
  m_shaderNameMap.insert(shaderNameMap::value_type("color", "colorDeffered"));
  m_shaderNameMap.insert(shaderNameMap::value_type("texture", "textureDeffered"));
  m_shaderNameMap.insert(shaderNameMap::value_type("specular", "specularDeffered"));
  m_shaderNameMap.insert(shaderNameMap::value_type("bump", "bumpDeffered"));
  m_shaderNameMap.insert(shaderNameMap::value_type("bumpSpec", "bumpSpecDeffered"));
  m_shaderNameMap.insert(shaderNameMap::value_type("bumpSpecMap", "bumpSpecMapDeffered"));

  m_shaderNameMap.insert(shaderNameMap::value_type("grid", "grid"));

  m_shaderNameMap.insert(shaderNameMap::value_type("ambientDeffered", "ambientDeffered"));
  m_shaderNameMap.insert(shaderNameMap::value_type("depthBuffer", "depthBuffer"));
  m_shaderNameMap.insert(shaderNameMap::value_type("pointLightDeffered", "pointLightDeffered"));
}

std::wstring ShaderConfiguration::GetVertexShaderFileName(const std::string& shaderName)
{
  std::wstring shaderNameUnicode(shaderName.begin(), shaderName.end());
  std::wstring templatePath = m_pathToVertexShader;
  size_t firstPos = templatePath.find(m_shaderNameParam);
  templatePath.replace(firstPos, m_shaderNameParam.length(), shaderNameUnicode);
  return templatePath;
}

std::wstring ShaderConfiguration::GetPixelShaderFileName(const std::string& shaderName)
{
  std::wstring shaderNameUnicode(shaderName.begin(), shaderName.end());
  std::wstring templatePath = m_pathToPixelShader;
  size_t firstPos = templatePath.find(m_shaderNameParam);
  templatePath.replace(firstPos, m_shaderNameParam.length(), shaderNameUnicode);
  return templatePath;
}

const std::string& ShaderConfiguration::GetConfiguredShaderName(const std::string& shaderName)
{
  return m_shaderNameMap[shaderName];
}