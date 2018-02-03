#pragma once

#include <vector>
#include "IShaderCreator.h"
#include "TemplateShaderCreator.h"
#include "GridShader.h"
#include "ColorShader.h"
#include "TextureShader.h"
#include "SingleDirectLightShader.h"
#include "SpecularSingleDirLightShader.h"
#include "BumpSingleDirLightShader.h"
#include "BumpSpecSingleLightSh.h"
#include "BumpSpecMapShader.h"
#include "ColorDefferedShader.h"
#include "SpecularDefferedShader.h"
#include "TextureDefferedShader.h"
#include "BumpDefferedShader.h"
#include "BumpSpecDefferedShader.h"
#include "BumpSpecMapDefferedShader.h"
#include "AmbientDefferedShader.h"
#include "DepthBufferShader.h"
#include "PointLightDefferedShader.h"
#include "PointLightTesselatedShader.h"
#include "ShaderConfiguration.h"
#include "Logger.h"

class ShaderFactory
{
private:
  static const std::string COLOR_SHADER_NAME;
  static const std::string TEXTURE_SHADER_NAME;
  static const std::string SINGLE_DIRECT_LIGHT_SHADER_NAME;
  static const std::string SPECULAR_DIRECT_LIGHT_SHADER_NAME;
  static const std::string BUMP_DIRECT_LIGHT_SHADER_NAME;
  static const std::string BUMP_SPEC_DIRECT_LIGHT_SHADER_NAME;
  static const std::string BUMP_SPEC_MAP_DIRECT_LIGHT_SHADER_NAME;
  static const std::string GRID_SHADER_NAME;
  static const std::string COLOR_DEFFERED_SHADER_NAME;
  static const std::string SPECULAR_DEFFERED_SHADER_NAME;
  static const std::string TEXTURE_DEFFERED_SHADER_NAME;
  static const std::string BUMP_DEFFERED_SHADER_NAME;
  static const std::string BUMP_SPEC_DEFFERED_SHADER_NAME;
  static const std::string BUMP_SPECMAP_DEFFERED_SHADER_NAME;
  static const std::string AMBIENT_DEFFERED_SHADER_NAME;
  static const std::string DEPTH_BUFFER_SHADER_NAME;
  static const std::string POINT_LIGHT_DEFFERED_SHADER_NAME;
  static const std::string POINT_LIGHT_TESSELATED_SHADER_NAME;
private:
  std::vector<IShaderCreator* > m_shaderCreators;
  ShaderConfiguration* m_shaderConfiguration;
public:
  ShaderFactory* Initialize(ID3D11Device* device, HWND hwnd, ShaderConfiguration* shaderConfiguration);
  void Shutdown();
  IShader* Get(const std::string& shaderName);
  ShaderFactory() { }
  virtual ~ShaderFactory();
};

