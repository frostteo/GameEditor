#include "ConfigurePLRelativePosWidget.h"

ConfigurePLRelativePosWidget::ConfigurePLRelativePosWidget(MapEditorPreferences* mapEditorPreferences, QString pathToModels, QString pathToMaterials, QWidget *parent)
  : QtDirectXWidget(pathToModels, pathToMaterials, parent)
{
  this->setWindowTitle("configure point light relative position");
  m_mapEditorPreferences = mapEditorPreferences;
  auto defautPointLightSgo = DependencyResolver::GetPointLightOnMapService()->GetDefaultPointLightSgo();


  m_pointLightSgo.SetModel(GetModel(defautPointLightSgo.modelFileName.toStdString()));
  m_pointLightSgo.SetParent(&m_sgo);
  m_control = new ConfigurePLRelPosControl(this, m_Camera.get(), &m_pointLightSgo, m_mapEditorPreferences);
  m_inputSystem->AddInputListener(m_control);
}


ConfigurePLRelativePosWidget::~ConfigurePLRelativePosWidget()
{
  Shutdown();
}

void ConfigurePLRelativePosWidget::SetPointLight(PointLightDbInfo& pointLight)
{
  if (!pointLight.staticGameObjectId)
    RUNTIME_ERROR("to configure point light relative position widget setted point light wihout static game object");

  m_pointLightId = pointLight.id;
  m_sgo = StaticGameObject();
  m_sgo.SetModel(GetModel(pointLight.staticGameObjectDbInfo.modelFileName.toStdString()));

  m_pointLightSgo.SetPosition(pointLight.relativePosX, pointLight.relativePosY, pointLight.relativePosZ);

  GEMath::LookToObjectFromWorldFront(m_Camera.get(), &m_sgo);
}

void ConfigurePLRelativePosWidget::paintEvent(QPaintEvent* pEvent)
{
  XMMATRIX worldMatrix;
  m_sgo.GetWorldMatrix(worldMatrix);
  m_graphicSystem->AddModelToRenderList(m_sgo.GetModel(), worldMatrix);

  m_pointLightSgo.GetWorldMatrix(worldMatrix);
  m_graphicSystem->AddModelToRenderList(m_pointLightSgo.GetModel(), worldMatrix);

  QtDirectXWidget::paintEvent(pEvent);
}

void ConfigurePLRelativePosWidget::EmitPointLightPositionChanged()
{
  XMFLOAT3 position = m_pointLightSgo.GetPosition();
  emit PointLightPositionChanged(m_pointLightId, position.x, position.y, position.z);
}

void ConfigurePLRelativePosWidget::CheckPointLightPosChanged(PointLightDbInfo& pointLight)
{
  if (m_pointLightId == pointLight.id)
  {
    m_pointLightSgo.SetPosition(pointLight.relativePosX, pointLight.relativePosY, pointLight.relativePosZ);
  }
}