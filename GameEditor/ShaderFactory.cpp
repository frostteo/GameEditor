#include "ShaderFactory.h"

void ShaderFactory::Initialize(ID3D11Device* device, HWND hwnd, ShaderConfiguration* shaderConfiguration)
{
  m_shaderConfiguration = shaderConfiguration;

  m_shaderCreators.push_back((new TextureShaderCreator())->Initialize(device, hwnd));
  m_shaderCreators.push_back((new SingleDirectLightShaderCreator())->Initialize(device, hwnd));
  m_shaderCreators.push_back((new SpecularSingleDirLightShaderCreator())->Initialize(device, hwnd));
  m_shaderCreators.push_back((new BumpSingleDirLightShaderCreator())->Initialize(device, hwnd));
  m_shaderCreators.push_back((new BumpSpecSingleLightShCreator())->Initialize(device, hwnd));
  m_shaderCreators.push_back((new BumpSpecMapShaderCreator())->Initialize(device, hwnd));
}


ShaderFactory::~ShaderFactory()
{
  for (auto shaderCreator : m_shaderCreators)
  {
    delete shaderCreator;
    shaderCreator = nullptr;
  }
}

IShader* ShaderFactory::Get(const std::string& shaderName)
{
  std::string configuredShaderName = m_shaderConfiguration->GetConfiguredShaderName(shaderName);

  if (configuredShaderName == "")
    Logger::get().LogMessageWithExceptionDialog("There is no shader with name " + shaderName + " in system", __FILE__, __LINE__);
  
  for (auto shaderCreator : m_shaderCreators)
  {
    if (shaderCreator->CanCreate(configuredShaderName))
      return shaderCreator->Get(m_shaderConfiguration->GetVertexShaderFileName(configuredShaderName), m_shaderConfiguration->GetPixelShaderFileName(configuredShaderName));
  }

  throw new std::runtime_error(Logger::get().GetErrorTraceMessage("there is no shader with name: " + shaderName + " in system", __FILE__, __LINE__));
}
