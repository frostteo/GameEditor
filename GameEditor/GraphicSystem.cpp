#include "GraphicSystem.h"


GraphicSystem::GraphicSystem()
{
}


GraphicSystem::~GraphicSystem()
{
}

void GraphicSystem::Initialize(int screenWidth, int screenHeight, bool vsyncEnabled, HWND hwnd, bool fullScreen, ShaderConfiguration* shaderConfiguration)
{
  m_direct3D = std::unique_ptr<D3DConfigurer>(new D3DConfigurer);
  m_direct3D->Initialize(screenWidth, screenHeight, vsyncEnabled, hwnd, fullScreen);
  if (!m_direct3D)
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("cant initialize direct 3D", __FILE__, __LINE__));

  //factory initializing
  MeshFactory::get().SetDevice(m_direct3D->GetDevice());
  TextureFactory::get().Initialize(m_direct3D->GetDevice(), m_direct3D->GetDeviceContext());
  ShaderFactory::get().Initialize(m_direct3D->GetDevice(), hwnd, shaderConfiguration);
  MaterialFactory::get().Initialize();
}

void GraphicSystem::DrawStatics(std::vector<Static*>& staticGameObjects, Camera* camera, LightininigSystem* lightiningSystem)
{
  XMMATRIX viewMatrix, projectionMatrix;

  // Clear the buffers to begin the scene.
  m_direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

  // Generate the view matrix based on the camera's position.
  camera->GetViewMatrix(viewMatrix);
  camera->GetProjectionMatrix(projectionMatrix);

  for (auto staticGameObject : staticGameObjects)
    staticGameObject->Render(m_direct3D->GetDeviceContext(), viewMatrix, projectionMatrix, lightiningSystem, camera->GetPosition());

  // Present the rendered scene to the screen.
  m_direct3D->EndScene();
}
