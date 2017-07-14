#include "ShaderFactory.h"

void ShaderFactory::Initialize(ID3D11Device* device, HWND hwnd, ShaderConfiguration* shaderConfiguration)
{
  m_shaderConfiguration = shaderConfiguration;

  m_shaderCreators.push_back(new TextureShaderCreator(device, hwnd));
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
  for (auto shaderCreator : m_shaderCreators)
  {
    if (shaderCreator->CanCreate(configuredShaderName))
      return shaderCreator->Get(m_shaderConfiguration->GetVertexShaderFileName(configuredShaderName), m_shaderConfiguration->GetPixelShaderFileName(configuredShaderName));
  }

  return nullptr;
}
