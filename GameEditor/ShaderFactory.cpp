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
const std::string ShaderFactory::DEPTH_BUFFER_SHADER_NAME = "depthBuffer";
const std::string ShaderFactory::AMBIENT_DEFFERED_SHADER_NAME = "ambientDeffered";
const std::string ShaderFactory::POINT_LIGHT_TESSELATED_SHADER_NAME = "pointLightTesselated";
const std::string ShaderFactory::PL_SHADOW_GEN_SHADER_NAME = "PLShadowGeneration";
const std::string ShaderFactory::PL_SHADOWED_TESS_SHADER_NAME = "pointLightDefferedWithShadow";

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
  m_shaderCreators.push_back(new TemplateShaderCreator<DepthBufferShader, DEPTH_BUFFER_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<PointLightDefferedShader, POINT_LIGHT_DEFFERED_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<PointLightTesselatedShader, POINT_LIGHT_TESSELATED_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<PLShadowGenerationShader, PL_SHADOW_GEN_SHADER_NAME>());
  m_shaderCreators.push_back(new TemplateShaderCreator<PLShadowedTesselatedShader, PL_SHADOWED_TESS_SHADER_NAME>());

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
 

  if (!m_shaderConfiguration->IsThisShaderInMap(shaderName))
    Logger::get().LogMessageWithExceptionDialog("There is no shader with name " + shaderName + " in system", __FILE__, __LINE__);
  
  std::string configuredShaderName = m_shaderConfiguration->GetConfiguredShaderName(shaderName);

  for (auto shaderCreator : m_shaderCreators)
  {
    if (shaderCreator->CanCreate(configuredShaderName))
      return shaderCreator->Get(
      m_shaderConfiguration->GetVertexShaderFileName(shaderName), 
      m_shaderConfiguration->GetGeometricShaderFileName(shaderName),
      m_shaderConfiguration->GetHullShaderFileName(shaderName),
      m_shaderConfiguration->GetDomainShaderFileName(shaderName),
      m_shaderConfiguration->GetPixelShaderFileName(shaderName)
      );
  }

  RUNTIME_ERROR("there is no shader with name: " + shaderName + " in system");
}
