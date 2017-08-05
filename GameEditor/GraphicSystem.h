#pragma once

#include <memory>
#include <vector>
#include <stdexcept>
#include "D3DConfigurer.h"
#include "Logger.h"
#include "Static.h"
#include "Camera.h"
#include "LightininigSystem.h"
#include "ShaderConfiguration.h"
#include "MeshFactory.h"
#include "MaterialFactory.h"
#include "TextureFactory.h"
#include "ShaderFactory.h"

class GraphicSystem
{
private:
  std::unique_ptr<D3DConfigurer> m_direct3D;
  std::unique_ptr<MeshFactory> m_meshFactory;
  std::unique_ptr<TextureFactory> m_textureFactory;
  std::unique_ptr<ShaderFactory> m_shaderFactory;
  std::unique_ptr<MaterialFactory> m_materialFactory;
public:
  GraphicSystem();
  virtual ~GraphicSystem();
  void Initialize(int screenWidth, int screenHeight, bool vsyncEnabled, HWND hwnd, bool fullScreen, ShaderConfiguration* shaderConfiguration);
  void DrawStatics(std::vector<Static*>& staticGameObjects, Camera* camera, LightininigSystem* lightiningSystem);
  MeshFactory* GetMeshFactory();
  TextureFactory* GetTextureFactory();
  ShaderFactory* GetShaderFactory();
  MaterialFactory* GetMaterialFactory();
};

