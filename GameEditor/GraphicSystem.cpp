#include "GraphicSystem.h"

const std::string GraphicSystem::GRID_SHADER_NAME = "grid";

GraphicSystem::GraphicSystem()
{
}


GraphicSystem::~GraphicSystem()
{
  
}

void GraphicSystem::Initialize(int screenWidth, int screenHeight, bool vsyncEnabled, HWND hwnd, bool fullScreen, ShaderConfiguration* shaderConfiguration, std::string pathToMaterials)
{
  bool result;
  m_direct3D = std::unique_ptr<D3DConfigurer>(new D3DConfigurer);
  result = m_direct3D->Initialize(screenWidth, screenHeight, vsyncEnabled, hwnd, fullScreen);
  if (!result)
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("cant initialize direct 3D", __FILE__, __LINE__));

  //factory initializing
  m_textureFactory = std::unique_ptr<TextureFactory>((new TextureFactory())->Initialize(m_direct3D->GetDevice(), m_direct3D->GetDeviceContext(), pathToMaterials));
  m_shaderFactory = std::unique_ptr<ShaderFactory>((new ShaderFactory())->Initialize(m_direct3D->GetDevice(), hwnd, shaderConfiguration));
  m_materialFactory = std::unique_ptr<MaterialFactory>((new MaterialFactory())->Initialize(m_textureFactory.get(), pathToMaterials)); //TODO FHolod: later give this as parameter
  m_modelFactory = std::unique_ptr<ModelFactory>((new ModelFactory())->Initialize(m_direct3D->GetDevice(), m_materialFactory.get()));
}

ModelFactory* GraphicSystem::GetModelFactory()
{
  return m_modelFactory.get();
}
TextureFactory* GraphicSystem::GetTextureFactory()
{
  return m_textureFactory.get();
}
ShaderFactory* GraphicSystem::GetShaderFactory()
{
  return m_shaderFactory.get();
}
MaterialFactory* GraphicSystem::GetMaterialFactory()
{
  return m_materialFactory.get();
}

void GraphicSystem::AddModelToRenderList(Model* model, XMMATRIX& worldMatrix)
{
  for (int i = 0; i < model->GetMeshCount(); ++i)
  {
    Mesh* mesh = model->GetMesh(i);
    std::pair<XMMATRIX, Mesh*> renderInfo(worldMatrix, mesh);
    m_modelRenderList[mesh->GetMaterialType()][mesh->GetMaterialName()].push_back(renderInfo);
  }
}

void GraphicSystem::Render(Camera* camera, LightininigSystem* lightiningSystem)
{
  XMMATRIX viewMatrix, projectionMatrix;

  // Clear the buffers to begin the scene.
  m_direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

  // Generate the view matrix based on the camera's position.
  camera->GetViewMatrix(viewMatrix);
  camera->GetProjectionMatrix(projectionMatrix);

  DrawModels(viewMatrix, projectionMatrix, lightiningSystem, camera->GetPosition());
  DrawGrids(viewMatrix, projectionMatrix);
  m_direct3D->EndScene();
}

void GraphicSystem::DrawModels(XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix, LightininigSystem* lightiningSystem, XMFLOAT3 cameraPosition)
{
  ID3D11DeviceContext* deviceContext = m_direct3D->GetDeviceContext();

  // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  for (auto shaderInfo : m_modelRenderList)
  {
    IShader* shader = m_shaderFactory->Get(shaderInfo.first);
    shader->EnableShader(deviceContext);

    for (auto materialInfo : shaderInfo.second)
    {
      IMaterial* material = materialInfo.second[0].second->GetMaterial();
      if (material->GetTexturesCount() > 0)
        shader->SetTextures(deviceContext, material->GetTextures(), material->GetTexturesCount());

      bool needEnableTransparancy = material->GetType() == ColorMaterial::colorMaterialType && (int)(((ColorMaterial*)material)->m_subType & ColorMaterialSubType::COLOR_TRANSPARENT) > 0;

      if (needEnableTransparancy)
        m_direct3D->TurnOnAlphaBlending();

      for (auto meshInfo : materialInfo.second)
      {
        meshInfo.second->PrepareToRender(deviceContext);
        shader->Render(deviceContext, meshInfo.second->GetIndexCount(), meshInfo.first, viewMatrix, projectionMatrix, material, lightiningSystem, cameraPosition);
      }

      if (needEnableTransparancy)
        m_direct3D->TurnOffAlphaBlending();
    }
  }
  m_modelRenderList.clear();
}

void GraphicSystem::DrawGrids(XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix)
{
  XMFLOAT3 nothing;
  auto deviceContext = m_direct3D->GetDeviceContext();
  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

  IShader* shader = GetShaderFactory()->Get(GRID_SHADER_NAME);
  shader->EnableShader(deviceContext);
  for (auto& gridAndWorldMatrix : m_gridObjectRenderList)
  {
    gridAndWorldMatrix.second->PrepareToRender(deviceContext);
    shader->Render(deviceContext, gridAndWorldMatrix.second->GetIndexCount(), gridAndWorldMatrix.first, viewMatrix, projectionMatrix, nullptr, nullptr, nothing);
  }
  m_gridObjectRenderList.clear();
}

void GraphicSystem::AddGridToRenderList(GridObject* gridObject, XMMATRIX& worldMatrix)
{
  m_gridObjectRenderList.push_back(std::pair<XMMATRIX, GridObject*>(worldMatrix, gridObject));
}