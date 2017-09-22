#pragma once

#include <memory>
#include <vector>
#include <stdexcept>
#include "D3DConfigurer.h"
#include "Logger.h"
#include "Model.h"
#include "Camera.h"
#include "LightininigSystem.h"
#include "ShaderConfiguration.h"
#include "ModelFactory.h"
#include "MaterialFactory.h"
#include "TextureFactory.h"
#include "ShaderFactory.h"

class GraphicSystem
{
private:
  std::unique_ptr<D3DConfigurer> m_direct3D;
  std::unique_ptr<ModelFactory> m_modelFactory;
  std::unique_ptr<TextureFactory> m_textureFactory;
  std::unique_ptr<ShaderFactory> m_shaderFactory;
  std::unique_ptr<MaterialFactory> m_materialFactory;
public:
  GraphicSystem();
  virtual ~GraphicSystem();
  void Initialize(int screenWidth, int screenHeight, bool vsyncEnabled, HWND hwnd, bool fullScreen, ShaderConfiguration* shaderConfiguration, std::string pathToMaterials);
  void DrawModels(std::vector<Model*>& staticGameObjects, Camera* camera, LightininigSystem* lightiningSystem);
  ModelFactory* GetModelFactory();
  TextureFactory* GetTextureFactory();
  ShaderFactory* GetShaderFactory();
  MaterialFactory* GetMaterialFactory();
};

