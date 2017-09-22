#include "GraphicSystem.h"


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
  m_modelFactory = std::unique_ptr<ModelFactory>((new ModelFactory())->Initialize(m_direct3D->GetDevice(), m_shaderFactory.get(), m_materialFactory.get()));
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

void GraphicSystem::DrawModels(std::vector<Model*>& models, Camera* camera, LightininigSystem* lightiningSystem)
{
  XMMATRIX viewMatrix, projectionMatrix;

  // Clear the buffers to begin the scene.
  m_direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

  // Generate the view matrix based on the camera's position.
  camera->GetViewMatrix(viewMatrix);
  camera->GetProjectionMatrix(projectionMatrix);

  for (auto model : models)
    model->Render(m_direct3D->GetDeviceContext(), viewMatrix, projectionMatrix, lightiningSystem, camera->GetPosition());

  // Present the rendered scene to the screen.
  m_direct3D->EndScene();
}
