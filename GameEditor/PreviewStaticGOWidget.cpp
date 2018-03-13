#include "PreviewStaticGOWidget.h"



PreviewStaticGOWidget::PreviewStaticGOWidget(MapEditorPreferences* mapEditorPreferences, QString pathToModels, QString pathToMaterials, QWidget *parent)
  : QtDirectXWidget(pathToModels, pathToMaterials, parent)
{
  this->setWindowTitle("Preview static game object");
  m_mapEditorPreferences = mapEditorPreferences;
}

bool PreviewStaticGOWidget::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
  return QtDirectXWidget::Initialize(screenWidth, screenHeight, hwnd);
}

PreviewStaticGOWidget::~PreviewStaticGOWidget()
{
  
}

void PreviewStaticGOWidget::SetStaticGameObject(StaticGameObjectDbInfo staticGameObject)
{
  m_inputSystem->ClearListenersList();

  m_sgo = StaticGameObject();
  m_sgo.SetModel(GetModel(staticGameObject.modelFileName.toStdString()));

  std::shared_ptr<PreviewGameObject> previewGameObject(new PreviewGameObject(m_Camera.get(), &m_sgo, m_mapEditorPreferences));
  m_inputSystem->AddInputListener(previewGameObject);

  GEMath::LookToObjectFromWorldFront(m_Camera.get(), &m_sgo);
}

void PreviewStaticGOWidget::paintEvent(QPaintEvent* evt) {
  XMMATRIX worldMatrix;
  m_sgo.GetWorldMatrix(worldMatrix);
  m_graphicSystem->AddModelToRenderList(*m_sgo.GetModel(), worldMatrix);

  QtDirectXWidget::paintEvent(evt);
}