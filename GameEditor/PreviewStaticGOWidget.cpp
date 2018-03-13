#include "PreviewStaticGOWidget.h"
#include "GEMath.h"
#include "PreviewGameObject.h"
#include "StaticGameObject.h"
#include "StaticGameObjectDbInfo.h"
#include "MapEditorPreferences.h"
#include "PathesToShaderSet.h"

PreviewStaticGOWidget::PreviewStaticGOWidget(
  MapEditorPreferences* mapEditorPreferences,
  const std::string& pathToModels,
  const std::string& pathToMaterials,
  const PathesToShaderSet& pathesToShaderSet,
  QWidget *parent
  )
  : QtDirectXWidget(pathToModels, pathToMaterials, pathesToShaderSet, parent),
  m_mapEditorPreferences(mapEditorPreferences),
  m_sgo(nullptr)
{
  this->setWindowTitle("Preview static game object");
}

bool PreviewStaticGOWidget::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
  return QtDirectXWidget::Initialize(screenWidth, screenHeight, hwnd);
}

PreviewStaticGOWidget::~PreviewStaticGOWidget()
{
  
}

void PreviewStaticGOWidget::SetStaticGameObject(const StaticGameObjectDbInfo& staticGameObject)
{
  m_inputSystem->ClearListenersList();

  m_sgo.reset(new StaticGameObject());
  m_sgo->SetModel(GetModel(staticGameObject.modelFileName.toStdString()));

  std::shared_ptr<PreviewGameObject> previewGameObject(new PreviewGameObject(m_Camera.get(), m_sgo.get(), m_mapEditorPreferences));
  m_inputSystem->AddInputListener(previewGameObject);

  GEMath::LookToObjectFromWorldFront(m_Camera.get(), m_sgo.get());
}

void PreviewStaticGOWidget::paintEvent(QPaintEvent* evt) {
  XMMATRIX worldMatrix;
  m_sgo->GetWorldMatrix(worldMatrix);
  m_graphicSystem->AddModelToRenderList(*m_sgo->GetModel(), worldMatrix);

  QtDirectXWidget::paintEvent(evt);
}