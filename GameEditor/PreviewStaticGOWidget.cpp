#include "PreviewStaticGOWidget.h"



PreviewStaticGOWidget::PreviewStaticGOWidget(QString pathToModels, QString pathToMaterials, QWidget *parent)
  : QtDirectXWidget(pathToModels, pathToMaterials, parent)
{
  this->setWindowTitle("Preview static game object");
}

bool PreviewStaticGOWidget::Initialize(int screenWidth, int screenHeight, HWND hwnd, std::string pathToMaterials)
{
  return QtDirectXWidget::Initialize(screenWidth, screenHeight, hwnd, pathToMaterials);
}

PreviewStaticGOWidget::~PreviewStaticGOWidget()
{
  Shutdown();
}

void PreviewStaticGOWidget::SetStaticGameObject(StaticGameObjectDbInfo staticGameObject)
{
  m_inputSystem->ClearListenersList();

  m_model = m_graphicSystem->GetModelFactory()->GetResource(m_pathToModels + FileProcessor::FILE_SEPARATOR + staticGameObject.modelFileName.toStdString());

  PreviewGameObject* previewGameObject = new PreviewGameObject();
  previewGameObject->SetCamera(m_Camera.get());
  previewGameObject->SetModel(m_model);
  m_inputSystem->AddInputListener(previewGameObject);
}

void PreviewStaticGOWidget::Shutdown()
{
  QtDirectXWidget::Shutdown();
}

void PreviewStaticGOWidget::paintEvent(QPaintEvent* evt) {
  m_graphicSystem->AddModelToRenderList(m_model);

  QtDirectXWidget::paintEvent(evt);
}