#pragma once

#include <memory>
#include <vector>
#include <map>
#include <stdexcept>
#include "D3DConfigurer.h"
#include "Logger.h"
#include "Camera.h"
#include "LightininigSystem.h"
#include "ShaderConfiguration.h"
#include "ModelFactory.h"
#include "MaterialFactory.h"
#include "TextureFactory.h"
#include "ShaderFactory.h"
#include "GridObject.h"
#include "StaticGameObject.h"
#include "PointLightDefferedParameters.h"

class GraphicSystem
{
private:
  const static std::string GRID_SHADER_NAME;
  const static std::string AMBIENT_DEFFERED_SHADER_NAME;
  const static std::string DEPTH_BUFFER_SHADER_NAME;
  const static std::string POINT_LIGHT_DEFFERED_SHADER_NAME;
  const static std::string POINT_LIGHT_MODEL_NAME;

  std::unique_ptr<D3DConfigurer> m_direct3D;
  std::unique_ptr<ModelFactory> m_modelFactory;
  std::unique_ptr<TextureFactory> m_textureFactory;
  std::unique_ptr<ShaderFactory> m_shaderFactory;
  std::unique_ptr<MaterialFactory> m_materialFactory;

  std::map<std::string, std::map<std::string, std::vector<std::pair<XMMATRIX, Mesh*>>>> m_modelRenderList;
  std::vector<std::pair<XMMATRIX, GridObject*> > m_gridObjectRenderList;

  std::string m_pathToModels;
  Mesh* m_pointLightMesh;
  PointLightDefferedParameters m_pointLightDefferedParemeters;
protected:
  void DrawModels(XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix, LightininigSystem* lightiningSystem, XMFLOAT3 cameraPosition);
  void DrawModelsInDepthBuffer(XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix);
  void DrawGrids(XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix);
public:
  GraphicSystem();
  virtual ~GraphicSystem();
  void Initialize(int screenWidth, int screenHeight, bool vsyncEnabled, HWND hwnd, bool fullScreen, ShaderConfiguration* shaderConfiguration, std::string pathToMaterials, std::string pathToModels);
  ModelFactory* GetModelFactory();
  TextureFactory* GetTextureFactory();
  ShaderFactory* GetShaderFactory();
  MaterialFactory* GetMaterialFactory();

  void AddModelToRenderList(Model* model, XMMATRIX& worldMatrix);
  void AddGridToRenderList(GridObject* gridObject, XMMATRIX& worldMatrix);
  ID3D11Device* GetDevice() { return m_direct3D->GetDevice(); }
  void Render(Camera* camera, LightininigSystem* lightiningSystem);
  void RenderDeffered(Camera* camera, LightininigSystem* lightiningSystem);
};

