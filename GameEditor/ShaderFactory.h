#pragma once

#include <vector>
#include "IShaderCreator.h"
#include "TextureShaderCreator.h"
#include "SingleDirectLightShaderCreator.h"
#include "SpecularSingleDirLightShaderCreator.h"
#include "BumpSingleDirLightShaderCreator.h"
#include "BumpSpecSingleLightShCreator.h"
#include "BumpSpecMapShaderCreator.h"
#include "Singleton.h"
#include "ShaderConfiguration.h"
#include "Logger.h"

class ShaderFactory
{
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

