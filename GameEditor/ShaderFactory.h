#pragma once

#include <vector>
#include "IShaderCreator.h"
#include "TextureShaderCreator.h"
#include "SingleDirectLightShaderCreator.h"
#include "SpecularSingleDirLightShaderCreator.h"
#include "Singleton.h"
#include "ShaderConfiguration.h"
#include "Logger.h"

class ShaderFactory : public Singleton<ShaderFactory>
{
  friend class Singleton<ShaderFactory>;
private:
  std::vector<IShaderCreator* > m_shaderCreators;
  ShaderConfiguration* m_shaderConfiguration;
protected:
  ShaderFactory() { }
  virtual ~ShaderFactory();
public:
  void Initialize(ID3D11Device* device, HWND hwnd, ShaderConfiguration* shaderConfiguration);
  IShader* Get(const std::string& shaderName);
};

