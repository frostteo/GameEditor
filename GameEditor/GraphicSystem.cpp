#include "GraphicSystem.h"
#include "Logger.h"

const std::string GraphicSystem::GRID_SHADER_NAME = "grid";
const std::string GraphicSystem::DEPTH_BUFFER_SHADER_NAME = "depthBuffer";
const std::string GraphicSystem::AMBIENT_DEFFERED_SHADER_NAME = "ambientDeffered";
const std::string GraphicSystem::POINT_LIGHT_DEFFERED_SHADER_NAME = "pointLightDeffered";
const std::string GraphicSystem::POINT_LIGHT_MODEL_NAME = "sphere1cm.txt";
const std::string GraphicSystem::POINT_LIGHT_TESSELATED_DEF_SN = "pointLightTesselated";
const std::string GraphicSystem::POINT_LIGHT_SHADOW_GEN_SHADER_NAME = "PLShadowGeneration";
const std::string GraphicSystem::PL_SHADOWED_TESS_SHADER_NAME = "PLWithShadowTessDeff";

GraphicSystem::GraphicSystem()
{
}

GraphicSystem::~GraphicSystem()
{
  
}

void GraphicSystem::Initialize(int screenWidth, int screenHeight, bool vsyncEnabled, HWND hwnd, bool fullScreen, ShaderConfiguration* shaderConfiguration, std::string pathToMaterials, std::string pathToModels)
{
  bool result;
  m_direct3D = std::unique_ptr<D3DConfigurer>(new D3DConfigurer);
  result = m_direct3D->Initialize(screenWidth, screenHeight, vsyncEnabled, hwnd, fullScreen);
  if (!result)
    RUNTIME_ERROR("cant initialize direct 3D");

  m_pathToModels = pathToModels;

  //factory initializing
  m_textureFactory = std::unique_ptr<TextureFactory>((new TextureFactory())->Initialize(m_direct3D->GetDevice(), m_direct3D->GetDeviceContext(), pathToMaterials));
  m_shaderFactory = std::unique_ptr<ShaderFactory>((new ShaderFactory())->Initialize(m_direct3D->GetDevice(), hwnd, shaderConfiguration));
  m_materialFactory = std::unique_ptr<MaterialFactory>((new MaterialFactory())->Initialize(m_textureFactory.get(), pathToMaterials));
  m_modelFactory = std::unique_ptr<ModelFactory>((new ModelFactory())->Initialize(m_direct3D->GetDevice(), m_materialFactory.get()));

  m_pointLightMesh = m_modelFactory->GetResource(m_pathToModels + FileProcessor::FILE_SEPARATOR + POINT_LIGHT_MODEL_NAME)->GetMesh(0);
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

void GraphicSystem::AddModelToRenderList(Model* model, XMMATRIX& worldMatrix, bool castShadows)
{
  for (int i = 0; i < model->GetMeshCount(); ++i)
  {
    Mesh* mesh = model->GetMesh(i);
    MeshRenderInfo renderInfo(worldMatrix, mesh, castShadows);
    m_modelRenderList[mesh->GetMaterialType()][mesh->GetMaterialName()].push_back(renderInfo);
  }
}

void GraphicSystem::Render(Camera* camera, LightininigSystem* lightiningSystem)
{
  XMMATRIX viewMatrix, projectionMatrix;

  m_direct3D->SetBackBufferRenderTarget();
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

  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  for (auto shaderInfo : m_modelRenderList)
  {
    IShader* shader = m_shaderFactory->Get(shaderInfo.first);
    shader->EnableShader(deviceContext);

    for (auto materialInfo : shaderInfo.second)
    {
      IMaterial* material = materialInfo.second[0].mesh->GetMaterial();
      if (material->GetTexturesCount() > 0)
        shader->SetTextures(deviceContext, material->GetTextures(), material->GetTexturesCount());

      bool needEnableTransparancy = material->GetType() == ColorMaterial::colorMaterialType && (int)(((ColorMaterial*)material)->m_subType & ColorMaterialSubType::COLOR_TRANSPARENT) > 0;

      if (needEnableTransparancy)
        m_direct3D->EnableTransparencyBlending();

      for (auto meshInfo : materialInfo.second)
      {
        meshInfo.mesh->PrepareToRender(deviceContext);
        shader->Render(deviceContext, meshInfo.mesh->GetIndexCount(), meshInfo.worldMatrix, viewMatrix, projectionMatrix, material, lightiningSystem, cameraPosition);
      }

      if (needEnableTransparancy)
        m_direct3D->DisableBlending();
    }
  }
  m_modelRenderList.clear();
}

void GraphicSystem::DrawModelsToDepthBuffer(XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix)
{
  ID3D11DeviceContext* deviceContext = m_direct3D->GetDeviceContext();
  XMFLOAT3 space;

  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  auto depthBufferShader = m_shaderFactory->Get(DEPTH_BUFFER_SHADER_NAME);
  depthBufferShader->EnableShader(deviceContext);
  for (auto shaderInfo : m_modelRenderList)
  {
    for (auto materialInfo : shaderInfo.second)
    {
      for (auto meshInfo : materialInfo.second)
      {
        meshInfo.mesh->PrepareToRender(deviceContext);
        depthBufferShader->Render(deviceContext, meshInfo.mesh->GetIndexCount(), meshInfo.worldMatrix, viewMatrix, projectionMatrix, nullptr, nullptr, space);
      }
    }
  }
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

void GraphicSystem::GeneratePointLightShadows(LightininigSystem* lightiningSystem)
{
  XMFLOAT3 spaceFloat3;
  XMMATRIX spaceMatrix;
  ID3D11DeviceContext* deviceContext = m_direct3D->GetDeviceContext();

  m_direct3D->PrepareToPointLightShadowGeneration();
  auto pointLightShadowGenerateShader = m_shaderFactory->Get(POINT_LIGHT_SHADOW_GEN_SHADER_NAME);
  pointLightShadowGenerateShader->EnableShader(deviceContext);
  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  for (int i = 0; i < lightiningSystem->GetPointLightsCastShadows()->size(); ++i)
  {
    lightiningSystem->SetPointLightToRenderSelector(true, i);
    auto pointLight = lightiningSystem->GetPointLightToRender();
    pointLight->PrepareToShadowGeneration(m_direct3D->GetDeviceContext());

    for (auto shaderInfo : m_modelRenderList)
    {
      for (auto materialInfo : shaderInfo.second)
      {
        for (auto meshInfo : materialInfo.second)
        {
          if (!meshInfo.castShadows)
            continue;

          meshInfo.mesh->PrepareToRender(deviceContext);
          pointLightShadowGenerateShader->Render(deviceContext, meshInfo.mesh->GetIndexCount(), meshInfo.worldMatrix, spaceMatrix, spaceMatrix, nullptr, lightiningSystem, spaceFloat3);
        }
      }
    }
  }
}

void GraphicSystem::RenderDefferedTesselatedWithShadows(Camera* camera, LightininigSystem* lightiningSystem)
{
  XMMATRIX viewMatrix, projectionMatrix, worldMatrix;
  XMMATRIX spaceMatrix;
  XMFLOAT3 spaceFloat3, cameraPosition;
  ID3D11DeviceContext* deviceContext = m_direct3D->GetDeviceContext();

  camera->GetViewMatrix(viewMatrix);
  camera->GetProjectionMatrix(projectionMatrix);

  cameraPosition = camera->GetPosition();

  GeneratePointLightShadows(lightiningSystem);

  m_direct3D->SetCullBackRasterState();
  m_direct3D->SetGBufferRenderTargets();
  m_direct3D->ClearGBufferRenderTargets();
  m_direct3D->DisableBlending();
 
  DrawModels(viewMatrix, projectionMatrix, nullptr, cameraPosition);

  m_direct3D->SetBackBufferRenderTarget();
  m_direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
  m_direct3D->DisableDepthTest();
  m_direct3D->SetNullAsDepthBuffer();
  m_direct3D->PrepareToFullScreenDefferedEffect();

  auto ambientDefferedShader = m_shaderFactory->Get(AMBIENT_DEFFERED_SHADER_NAME);
  ambientDefferedShader->EnableShader(deviceContext);
  ambientDefferedShader->SetTextures(deviceContext, m_direct3D->GetGBufferShaderResourceViewes(), GBuffer::SHADER_RESOURCE_VIEW_COUNT);
  ambientDefferedShader->Render(deviceContext, 0, spaceMatrix, spaceMatrix, spaceMatrix, nullptr, lightiningSystem, spaceFloat3);

  m_direct3D->EnableAditiveBlending();

  camera->GetWorldMatrix(worldMatrix);
  m_pointLightDefferedParemeters.SetViewMatrixInverse(worldMatrix);
  m_pointLightDefferedParemeters.SetPerspectiveValues(projectionMatrix);

  m_direct3D->SetGBufferReadonlyDepthBufferToRenderTargets();
  m_direct3D->EnableGreaterEqualReadonlyDepthTest();
  m_direct3D->SetCullFrontRasterState();

  // Отрисовать вначале все источники с тенями
  auto pointLightWithShadow = m_shaderFactory->Get(PL_SHADOWED_TESS_SHADER_NAME);
  pointLightWithShadow->SetTextures(m_direct3D->GetDeviceContext(), m_direct3D->GetGBufferShaderResourceViewes(), GBuffer::SHADER_RESOURCE_VIEW_COUNT);
  pointLightWithShadow->EnableShader(deviceContext);

  for (int i = 0; i < lightiningSystem->GetPointLightsCastShadows()->size(); ++i)
  {
    lightiningSystem->SetPointLightToRenderSelector(true, i);
    auto pointLight = lightiningSystem->GetPointLightToRender();
    deviceContext->PSSetShaderResources(GBuffer::SHADER_RESOURCE_VIEW_COUNT, 1, pointLight->GetPointLightShadowBuffer());
    pointLightWithShadow->Render(deviceContext, 0, spaceMatrix, viewMatrix, projectionMatrix, &m_pointLightDefferedParemeters, lightiningSystem, cameraPosition);
  }

  // Отрисовать источники света без теней
  auto pointLightShader = m_shaderFactory->Get(POINT_LIGHT_TESSELATED_DEF_SN);
  pointLightShader->EnableShader(deviceContext);

  for (int i = 0; i < lightiningSystem->GetPointLightsNonCastShadows()->size(); ++i)
  {
    lightiningSystem->SetPointLightToRenderSelector(false, i);
    pointLightShader->Render(deviceContext, 0, spaceMatrix, viewMatrix, projectionMatrix, &m_pointLightDefferedParemeters, lightiningSystem, cameraPosition);
  }

  m_direct3D->SetCullBackRasterState();
  m_direct3D->EnableDepthTest();
  m_direct3D->DisableBlending();

  DrawGrids(viewMatrix, projectionMatrix);

  m_direct3D->EndScene();
}

void GraphicSystem::RenderDefferedTesselatedWithoutShadows(Camera* camera, LightininigSystem* lightiningSystem)
{
  XMMATRIX viewMatrix, projectionMatrix, worldMatrix;
  XMMATRIX spaceMatrix;
  XMFLOAT3 spaceFloat3, cameraPosition;
  ID3D11DeviceContext* deviceContext = m_direct3D->GetDeviceContext();

  camera->GetViewMatrix(viewMatrix);
  camera->GetProjectionMatrix(projectionMatrix);

  cameraPosition = camera->GetPosition();

  m_direct3D->SetCullBackRasterState();
  m_direct3D->SetGBufferRenderTargets();
  m_direct3D->ClearGBufferRenderTargets();
  m_direct3D->DisableBlending();

  DrawModels(viewMatrix, projectionMatrix, nullptr, cameraPosition);

  m_direct3D->SetBackBufferRenderTarget();
  m_direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
  m_direct3D->DisableDepthTest();
  m_direct3D->SetNullAsDepthBuffer();
  m_direct3D->PrepareToFullScreenDefferedEffect();

  auto ambientDefferedShader = m_shaderFactory->Get(AMBIENT_DEFFERED_SHADER_NAME);
  ambientDefferedShader->EnableShader(deviceContext);
  ambientDefferedShader->SetTextures(deviceContext, m_direct3D->GetGBufferShaderResourceViewes(), GBuffer::SHADER_RESOURCE_VIEW_COUNT);
  ambientDefferedShader->Render(deviceContext, 0, spaceMatrix, spaceMatrix, spaceMatrix, nullptr, lightiningSystem, spaceFloat3);

  m_direct3D->EnableAditiveBlending();

  camera->GetWorldMatrix(worldMatrix);
  m_pointLightDefferedParemeters.SetViewMatrixInverse(worldMatrix);
  m_pointLightDefferedParemeters.SetPerspectiveValues(projectionMatrix);

  m_direct3D->SetGBufferReadonlyDepthBufferToRenderTargets();
  m_direct3D->EnableGreaterEqualReadonlyDepthTest();
  m_direct3D->SetCullFrontRasterState();

  auto pointLightShader = m_shaderFactory->Get(POINT_LIGHT_TESSELATED_DEF_SN);
  pointLightShader->SetTextures(m_direct3D->GetDeviceContext(), m_direct3D->GetGBufferShaderResourceViewes(), GBuffer::SHADER_RESOURCE_VIEW_COUNT);
  pointLightShader->EnableShader(deviceContext);

  // Отрисовать без теней все источники с тенями
  for (int i = 0; i < lightiningSystem->GetPointLightsCastShadows()->size(); ++i)
  {
    lightiningSystem->SetPointLightToRenderSelector(true, i);
    pointLightShader->Render(deviceContext, 0, spaceMatrix, viewMatrix, projectionMatrix, &m_pointLightDefferedParemeters, lightiningSystem, cameraPosition);
  }

  // Отрисовать источники света без теней
  for (int i = 0; i < lightiningSystem->GetPointLightsNonCastShadows()->size(); ++i)
  {
    lightiningSystem->SetPointLightToRenderSelector(false, i);
    pointLightShader->Render(deviceContext, 0, spaceMatrix, viewMatrix, projectionMatrix, &m_pointLightDefferedParemeters, lightiningSystem, cameraPosition);
  }

  m_direct3D->SetCullBackRasterState();
  m_direct3D->EnableDepthTest();
  m_direct3D->DisableBlending();

  DrawGrids(viewMatrix, projectionMatrix);

  m_direct3D->EndScene();
}


void GraphicSystem::RenderDefferedStencilVolume(Camera* camera, LightininigSystem* lightiningSystem)
{
  XMMATRIX viewMatrix, projectionMatrix, worldMatrix;
  XMMATRIX spaceMatrix;
  XMFLOAT3 spaceFloat3;

  camera->GetViewMatrix(viewMatrix);
  camera->GetProjectionMatrix(projectionMatrix);

  m_direct3D->ClearGBufferRenderTargets();
  m_direct3D->DisableBlending();

  m_direct3D->SetGBufferRenderTargets();
  DrawModels(viewMatrix, projectionMatrix, nullptr, camera->GetPosition());

  m_direct3D->SetBackBufferRenderTarget();
  m_direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
  m_direct3D->DisableDepthTest();
  m_direct3D->SetNullAsDepthBuffer();
    m_direct3D->PrepareToFullScreenDefferedEffect();

  auto ambientDefferedShader = m_shaderFactory->Get(AMBIENT_DEFFERED_SHADER_NAME);
  ambientDefferedShader->EnableShader(m_direct3D->GetDeviceContext());
  ambientDefferedShader->SetTextures(m_direct3D->GetDeviceContext(), m_direct3D->GetGBufferShaderResourceViewes(), GBuffer::SHADER_RESOURCE_VIEW_COUNT);
  ambientDefferedShader->Render(m_direct3D->GetDeviceContext(), 0, spaceMatrix, spaceMatrix, spaceMatrix, nullptr, lightiningSystem, spaceFloat3);
  
  m_direct3D->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  m_direct3D->EnableAditiveBlending();

  auto depthBufferShader = m_shaderFactory->Get(DEPTH_BUFFER_SHADER_NAME);
  auto pointLightDefferedShader = m_shaderFactory->Get(POINT_LIGHT_DEFFERED_SHADER_NAME);

  camera->GetWorldMatrix(worldMatrix);
  m_pointLightDefferedParemeters.SetViewMatrixInverse(worldMatrix);
  m_pointLightDefferedParemeters.SetPerspectiveValues(projectionMatrix);

  for (int i = 0; i < lightiningSystem->GetPointLightsNonCastShadows()->size(); ++i)
  {
    lightiningSystem->SetPointLightToRenderSelector(false, i);

    auto pointLight = lightiningSystem->GetPointLightToRender();
    pointLight->GetWorldMatrix(worldMatrix);

    m_direct3D->SetGBufferOnlyWriteableDepthBufferToRenderTargets();
    m_direct3D->ClearGBufferStencil();
    m_direct3D->EnableDepthStencilLightVolumeState();
    m_direct3D->SetCullNoneRasterState();
    depthBufferShader->EnableShader(m_direct3D->GetDeviceContext());
    m_pointLightMesh->PrepareToRender(m_direct3D->GetDeviceContext());
    depthBufferShader->Render(m_direct3D->GetDeviceContext(), m_pointLightMesh->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, nullptr, nullptr, camera->GetPosition());

    m_direct3D->SetGBufferReadonlyDepthBufferToRenderTargets();
    m_direct3D->EnableDepthStencilDefferedLightState();
    m_direct3D->SetCullFrontRasterState();
    pointLightDefferedShader->SetTextures(m_direct3D->GetDeviceContext(), m_direct3D->GetGBufferShaderResourceViewes(), GBuffer::SHADER_RESOURCE_VIEW_COUNT);
    pointLightDefferedShader->EnableShader(m_direct3D->GetDeviceContext());
    m_pointLightMesh->PrepareToRender(m_direct3D->GetDeviceContext());
    pointLightDefferedShader->Render(m_direct3D->GetDeviceContext(), m_pointLightMesh->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, &m_pointLightDefferedParemeters, lightiningSystem, camera->GetPosition());
  }

  for (int i = 0; i < lightiningSystem->GetPointLightsCastShadows()->size(); ++i)
  {
    lightiningSystem->SetPointLightToRenderSelector(true, i);

    auto pointLight = lightiningSystem->GetPointLightToRender();
    pointLight->GetWorldMatrix(worldMatrix);

    m_direct3D->SetGBufferOnlyWriteableDepthBufferToRenderTargets();
    m_direct3D->ClearGBufferStencil();
    m_direct3D->EnableDepthStencilLightVolumeState();
    m_direct3D->SetCullNoneRasterState();
    depthBufferShader->EnableShader(m_direct3D->GetDeviceContext());
    m_pointLightMesh->PrepareToRender(m_direct3D->GetDeviceContext());
    depthBufferShader->Render(m_direct3D->GetDeviceContext(), m_pointLightMesh->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, nullptr, nullptr, camera->GetPosition());

    m_direct3D->SetGBufferReadonlyDepthBufferToRenderTargets();
    m_direct3D->EnableDepthStencilDefferedLightState();
    m_direct3D->SetCullFrontRasterState();
    pointLightDefferedShader->SetTextures(m_direct3D->GetDeviceContext(), m_direct3D->GetGBufferShaderResourceViewes(), GBuffer::SHADER_RESOURCE_VIEW_COUNT);
    pointLightDefferedShader->EnableShader(m_direct3D->GetDeviceContext());
    m_pointLightMesh->PrepareToRender(m_direct3D->GetDeviceContext());
    pointLightDefferedShader->Render(m_direct3D->GetDeviceContext(), m_pointLightMesh->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, &m_pointLightDefferedParemeters, lightiningSystem, camera->GetPosition());
  }

  m_direct3D->SetCullBackRasterState();
  m_direct3D->EnableDepthTest();
  m_direct3D->DisableBlending();

  DrawGrids(viewMatrix, projectionMatrix);

  m_direct3D->EndScene();
}