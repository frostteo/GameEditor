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

  m_sgo.SetModel(GetModel(staticGameObject.modelFileName.toStdString()));

  PreviewGameObject* previewGameObject = new PreviewGameObject();
  previewGameObject->SetCamera(m_Camera.get());
  previewGameObject->SetSGO(&m_sgo);
  m_inputSystem->AddInputListener(previewGameObject);
}

void PreviewStaticGOWidget::Shutdown()
{
  QtDirectXWidget::Shutdown();
}

void PreviewStaticGOWidget::paintEvent(QPaintEvent* evt) {
  XMMATRIX worldMatrix;
  m_sgo.GetWorldMatrix(worldMatrix);
  m_graphicSystem->AddModelToRenderList(m_sgo.GetModel(), worldMatrix);

  QtDirectXWidget::paintEvent(evt);
}