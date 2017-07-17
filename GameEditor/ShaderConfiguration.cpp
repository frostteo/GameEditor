#include "ShaderConfiguration.h"


ShaderConfiguration::ShaderConfiguration()
{

}


ShaderConfiguration::~ShaderConfiguration()
{
}

void ShaderConfiguration::Configure()
{
  m_pathToVertexShader = L"../GameEditor/shaders/[shadername].vs";
  m_pathToPixelShader = L"../GameEditor/shaders/[shadername].ps";

  //m_shaderNameMap.insert(shaderNameMap::value_type("texture", "texture"));
  m_shaderNameMap.insert(shaderNameMap::value_type("texture", "singleDirectLight"));
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