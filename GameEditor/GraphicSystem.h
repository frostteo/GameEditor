#pragma once

#include <memory>
#include <vector>
#include <map>
#include <stdexcept>
#include "D3DConfigurer.h"
#include "ShaderConfiguration.h"
#include "ModelFactory.h"
#include "MaterialFactory.h"
#include "TextureFactory.h"
#include "ShaderFactory.h"
#include "PointLightDefferedParameters.h"

class Logger;
class LightininigSystem;
class Camera;
class Mesh;
class GridObject;

class GraphicSystem
{
private:
  struct MeshRenderInfo
  {
    MeshRenderInfo(XMMATRIX worldMatrixArg, const Mesh* meshArg, bool castShadowsArg) : worldMatrix(worldMatrixArg), mesh(meshArg), castShadows(castShadowsArg) {}

    const XMMATRIX worldMatrix;
    const Mesh* mesh;
    const bool castShadows;
  };
private:
  const static std::string GRID_SHADER_NAME;
  const static std::string AMBIENT_DEFFERED_SHADER_NAME;
  const static std::string DEPTH_BUFFER_SHADER_NAME;
  const static std::string POINT_LIGHT_DEFFERED_SHADER_NAME;
  const static std::string POINT_LIGHT_TESSELATED_DEF_SN;
  const static std::string POINT_LIGHT_MODEL_NAME;
  const static std::string POINT_LIGHT_SHADOW_GEN_SHADER_NAME;
  const static std::string PL_SHADOWED_TESS_SHADER_NAME;

  std::unique_ptr<D3DConfigurer> m_direct3D;
  std::unique_ptr<ModelFactory> m_modelFactory;
  std::unique_ptr<TextureFactory> m_textureFactory;
  std::unique_ptr<ShaderFactory> m_shaderFactory;
  std::unique_ptr<MaterialFactory> m_materialFactory;

  std::map<std::string, std::map<std::string, std::vector<MeshRenderInfo>>> m_modelRenderList;
  std::vector<std::pair<const XMMATRIX, const GridObject*> > m_gridObjectRenderList;

  std::string m_pathToModels;
  Mesh* m_pointLightMesh;
  PointLightDefferedParameters m_pointLightDefferedParemeters;
protected:
  void DrawModels(XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix, LightininigSystem* lightiningSystem, XMFLOAT3 cameraPosition);
  void DrawModelsToDepthBuffer(XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix);
  void DrawGrids(XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix);
  void GeneratePointLightShadows(LightininigSystem* lightiningSystem);
public:
  GraphicSystem();
  virtual ~GraphicSystem();
  void Initialize(int screenWidth, int screenHeight, bool vsyncEnabled, HWND hwnd, bool fullScreen, ShaderConfiguration* shaderConfiguration, std::string pathToMaterials, std::string pathToModels);
  ModelFactory* GetModelFactory();
  TextureFactory* GetTextureFactory();
  ShaderFactory* GetShaderFactory();
  MaterialFactory* GetMaterialFactory();

  void AddModelToRenderList(const Model& model, const XMMATRIX& worldMatrix, const bool castShadow = true);
  void AddGridToRenderList(const GridObject* gridObject, const XMMATRIX& worldMatrix);
  ID3D11Device* GetDevice() { return m_direct3D->GetDevice(); }
  void Render(const Camera* camera, LightininigSystem* lightiningSystem);
  void RenderDefferedStencilVolume(const Camera* camera, LightininigSystem* lightiningSystem);
  void RenderDefferedTesselatedWithShadows(const Camera* camera, LightininigSystem* lightiningSystem);
  void RenderDefferedTesselatedWithoutShadows(const Camera* camera, LightininigSystem* lightiningSystem);

  D3DConfigurer* GetD3dConfigurer() { return m_direct3D.get(); }
};

