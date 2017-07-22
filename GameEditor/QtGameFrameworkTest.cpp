#include "QtGameFrameworkTest.h"

QtGameFrameworkTest::QtGameFrameworkTest(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    this->setWindowFlags(Qt::Window);

    //I dont know what it do? but it is for Qt working
    setMinimumSize(800, 600);
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_NativeWindow, true);

    bool result = Initialize(width(), height(), (HWND)winId());
    if (!result) {
      QMessageBox::critical(this,
        "ERROR",
        "Faild initizlize QD3Dwidget",
        QMessageBox::Ok);
    }
}

QtGameFrameworkTest::~QtGameFrameworkTest()
{
  Shutdown();
}

bool QtGameFrameworkTest::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
  bool result;

  m_shaderConfiguration = new ShaderConfiguration();
  m_shaderConfiguration->Configure();

  // Create the Direct3D object.
  m_Direct3D = new D3DConfigurer; 
  m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN);
  if (!m_Direct3D)
  {
    return false;
  }

  //factory initializing
  MeshFactory::get().SetDevice(m_Direct3D->GetDevice());
  TextureFactory::get().Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());
  ShaderFactory::get().Initialize(m_Direct3D->GetDevice(), hwnd, m_shaderConfiguration);
  MaterialFactory::get().Initialize();

  m_static.Initialize(MeshFactory::get().GetResource("../GameEditor/models/cube4.txt"), MaterialFactory::get().GetResource("../GameEditor/materials/woodBoxBumpSpec.mat"));

  // Create the camera object.
  m_Camera = new Camera(screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
  if (!m_Camera)
  {
    return false;
  }

  m_Camera->SetPosition(0.0f, 10.0f, -50.0f);

  m_lightininigSystem = new LightininigSystem();
  if (!m_lightininigSystem) 
  {
    return false;
  }
  m_lightininigSystem->SetDirectLightDirection(0.0f, 0.0f, 1.0f);
  m_lightininigSystem->SetDirectLightColor(1.0f, 1.0f, 1.0f, 1.0f);
  m_lightininigSystem->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);

  return true;
}

void QtGameFrameworkTest::Shutdown()
{
  if (m_shaderConfiguration)
  {
    delete m_shaderConfiguration;
    m_shaderConfiguration = nullptr;
  }

  if (m_Direct3D)
  {
    delete m_Direct3D;
    m_Direct3D = nullptr;
  }

  // Release the camera object.
  if (m_Camera)
  {
    delete m_Camera;
    m_Camera = nullptr;
  }

  if (m_lightininigSystem)
  {
    delete m_lightininigSystem;
    m_lightininigSystem = nullptr;
  }

  return;
}


void QtGameFrameworkTest::paintEvent(QPaintEvent* evt) {
  XMMATRIX viewMatrix, projectionMatrix;
  bool renderModel, result;

  // Clear the buffers to begin the scene.
  m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

  // Generate the view matrix based on the camera's position.
  m_Camera->GetViewMatrix(viewMatrix);
  m_Camera->GetProjectionMatrix(projectionMatrix);

  m_static.ChangeYRotation(0.5);

  m_static.Render(m_Direct3D->GetDeviceContext(), viewMatrix, projectionMatrix, m_lightininigSystem, m_Camera->GetPosition());

  XMMATRIX world;
  m_static.GetWorldMatrix(world);

  // Present the rendered scene to the screen.
  m_Direct3D->EndScene();

  // trigger another update as soon as possible 
  update();
}