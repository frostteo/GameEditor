#include "ShaderFactory.h"

const std::string ShaderFactory::COLOR_SHADER_NAME = "colorSingleDirLight";
const std::string ShaderFactory::TEXTURE_SHADER_NAME = "texture";
const std::string ShaderFactory::SINGLE_DIRECT_LIGHT_SHADER_NAME = "singleDirectLight";
const std::string ShaderFactory::SPECULAR_DIRECT_LIGHT_SHADER_NAME = "specularSingleDirLight";
const std::string ShaderFactory::BUMP_DIRECT_LIGHT_SHADER_NAME = "bump";
const std::string ShaderFactory::BUMP_SPEC_DIRECT_LIGHT_SHADER_NAME = "bumpSpec";
const std::string ShaderFactory::BUMP_SPEC_MAP_DIRECT_LIGHT_SHADER_NAME = "bumpSpecMap";
const std::string ShaderFactory::GRID_SHADER_NAME = "grid";

const std::string ShaderFactory::COLOR_DEFFERED_SHADER_NAME = "colorDeffered";
const std::string ShaderFactory::SPECULAR_DEFFERED_SHADER_NAME = "specularDeffered";
const std::string ShaderFactory::TEXTURE_DEFFERED_SHADER_NAME = "textureDeffered";
const std::string ShaderFactory::BUMP_DEFFERED_SHADER_NAME = "bumpDeffered";
const std::string ShaderFactory::BUMP_SPEC_DEFFERED_SHADER_NAME = "bumpSpecDeffered";
const std::string ShaderFactory::BUMP_SPECMAP_DEFFERED_SHADER_NAME = "bumpSpecMapDeffered";

const std::string ShaderFactory::POINT_LIGHT_DEFFERED_SHADER_NAME = "pointLightDeffered";
const std::string ShaderFactory::LIGHT_VOLUME_STENCIL_SHADER_NAME = "lightVolumeStencil";
const std::string ShaderFactory::AMBIENT_DEFFERED_SHADER_NAME = "ambientDeffered";

ShaderFactory* ShaderFactory::Initialize(ID3D11Device* device, HWND hwnd, ShaderConfiguration* shaderConfiguration)
{
  Shutdown();

  m_shaderConfiguration = shaderConfiguration;

  m_shaderCreators.push_back(new TemplateShaderCreator<ColorShader, COLOR_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<TextureShader, TEXTURE_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<SingleDirectLightShader, SINGLE_DIRECT_LIGHT_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<SpecularSingleDirLightShader, SPECULAR_DIRECT_LIGHT_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<BumpSingleDirLightShader, BUMP_DIRECT_LIGHT_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<BumpSpecSingleLightSh, BUMP_SPEC_DIRECT_LIGHT_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<BumpSpecMapShader, BUMP_SPEC_MAP_DIRECT_LIGHT_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<GridShader, GRID_SHADER_NAME>());

  m_shaderCreators.push_back(new TemplateShaderCreator<ColorDefferedShader, COLOR_DEFFERED_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<TextureDefferedShader, TEXTURE_DEFFERED_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<SpecularDefferedShader, SPECULAR_DEFFERED_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<BumpDefferedShader, BUMP_DEFFERED_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<BumpSpecDefferedShader, BUMP_SPEC_DEFFERED_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<BumpSpecMapDefferedShader, BUMP_SPECMAP_DEFFERED_SHADER_NAME>());

  m_shaderCreators.push_back(new TemplateShaderCreator<AmbientDefferedShader, AMBIENT_DEFFERED_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<LightVolumeStencilShader, LIGHT_VOLUME_STENCIL_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<PointLightDefferedShader, POINT_LIGHT_DEFFERED_SHADER_NAME>());

  for (auto& creator : m_shaderCreators)
    creator->Initialize(device, hwnd);

  return this;
}

void ShaderFactory::Shutdown()
{
  for (auto shaderCreator : m_shaderCreators)
  {
    delete shaderCreator;
    shaderCreator = nullptr;
  }
  m_shaderCreators.clear();
}

ShaderFactory::~ShaderFactory()
{
  Shutdown();
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
