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
  ObjMeshConverter objConverter;
 /* MtlMatLibConverter matConverter("../GameEditor/materials");
  objConverter.ConvertModel("../GameEditor/obj models/testCube.obj", "../GameEditor/models/cube.txt");
  std::string material = "../GameEditor/obj models/testCube.mtl";
  matConverter.ConvertMtlMaterials(material, true);*/

  m_shaderConfiguration = new ShaderConfiguration();
  m_shaderConfiguration->ConfigureForwardRenderer();

  m_graphicSystem = std::unique_ptr<GraphicSystem>(new GraphicSystem);
  if (!m_graphicSystem)
    return false;

  m_graphicSystem->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, m_shaderConfiguration, "../GameEditor/materials", "../GameEditor/models");

  //m_model = m_graphicSystem->GetModelFactory()->GetResource("../GameEditor/models/lamp.txt");
  //m_model = m_graphicSystem->GetModelFactory()->GetResource("../GameEditor/models/healthPotion.txt");
  m_sgo.SetModel(m_graphicSystem->GetModelFactory()->GetResource("../GameEditor/models/test column.txt"));
  //m_model = m_graphicSystem->GetModelFactory()->GetResource("../GameEditor/models/cube.txt");


  m_mapEditorPreferences = std::unique_ptr<MapEditorPreferences>(new MapEditorPreferences());

  // Create the camera object.
  m_Camera = new Camera();
  m_Camera->Initialize(screenWidth, screenHeight, m_screenNear, m_screenDepth);
  if (!m_Camera)
  {
    return false;
  }

  m_Camera->SetPosition(0.0f, 0.0f, -100.0f);

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

  PreviewGameObject* previewGameObject = new PreviewGameObject(m_Camera, &m_sgo, m_mapEditorPreferences.get());
  previewGameObject->SetCamera(m_Camera);
  previewGameObject->SetSGO(&m_sgo);
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
  XMMATRIX worldMatrix;
  m_sgo.GetWorldMatrix(worldMatrix);
  m_graphicSystem->AddModelToRenderList(m_sgo.GetModel(), worldMatrix);
  m_graphicSystem->Render(m_Camera, m_lightininigSystem);

  // trigger another update as soon as possible 
  update();
}

void QtGameFrameworkTest::resizeEvent(QResizeEvent* evt)
{
  //TODO FHolod: update resource which depends on aspect ration
  float width = this->width();
  float height = this->height();
  m_Camera->Initialize(width, height, m_screenNear, m_screenDepth);
}