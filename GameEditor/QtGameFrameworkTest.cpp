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

  HighPerformanceTimer::get().Initialize();
  HighPerformanceTimer::get().Frame();
 /* ObjMeshConverter objConverter;
  objConverter.ConvertModel("../GameEditor/models/CubeFromMax.obj", "../GameEditor/models/centeredCube.txt");*/

  m_shaderConfiguration = new ShaderConfiguration();
  m_shaderConfiguration->Configure();

  m_graphicSystem = std::unique_ptr<GraphicSystem>(new GraphicSystem);
  if (!m_graphicSystem)
    return false;

  m_graphicSystem->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, m_shaderConfiguration);

  m_static.Initialize(MeshFactory::get().GetResource("../GameEditor/models/centeredCube.txt"), MaterialFactory::get().GetResource("../GameEditor/materials/woodBoxBumpSpec.mat"));

  // Create the camera object.
  m_Camera = new Camera(screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
  if (!m_Camera)
  {
    return false;
  }

  m_Camera->SetPosition(0.0f, 0.0f, -50.0f);

  m_lightininigSystem = new LightininigSystem();
  if (!m_lightininigSystem) 
  {
    return false;
  }
  m_lightininigSystem->SetDirectLightDirection(1.0f, 0.0f, 1.0f);
  m_lightininigSystem->SetDirectLightColor(1.0f, 1.0f, 1.0f, 1.0f);
  m_lightininigSystem->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);

  m_inputSystem = new InputSystem();
  m_inputSystem->Initialize(GetModuleHandle(NULL), hwnd);

  PreviewGameObject* previewGameObject = new PreviewGameObject();
  previewGameObject->SetCamera(m_Camera);
  previewGameObject->SetStatic(&m_static);
  m_inputSystem->AddInputListener(previewGameObject);

  return true;
}

void QtGameFrameworkTest::Shutdown()
{
  if (m_shaderConfiguration)
  {
    delete m_shaderConfiguration;
    m_shaderConfiguration = nullptr;
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

  if (m_inputSystem) 
  {
    delete m_inputSystem;
    m_inputSystem = nullptr;
  }

  return;
}


void QtGameFrameworkTest::paintEvent(QPaintEvent* evt) {
  HighPerformanceTimer::get().Frame();

  m_inputSystem->Frame();
  std::vector<Static*> renderedStaticGO;
  renderedStaticGO.push_back(&m_static);
  m_graphicSystem->DrawStatics(renderedStaticGO, m_Camera, m_lightininigSystem);

  // trigger another update as soon as possible 
  update();
}