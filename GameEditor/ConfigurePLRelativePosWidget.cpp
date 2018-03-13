#include "ConfigurePLRelativePosWidget.h"
#include "ConfigurePLRelPosControl.h"
#include "DependencyResolver.h"
#include "PointLightDbInfo.h"
#include "StaticGameObject.h"
#include "PathesToShaderSet.h"
#include "MapEditorPreferences.h"

ConfigurePLRelativePosWidget::ConfigurePLRelativePosWidget(
  MapEditorPreferences* mapEditorPreferences,
  const std::string& pathToModels,
  const std::string& pathToMaterials,
  const PathesToShaderSet& pathesToShaderSet, 
  QWidget *parent
  )
  : QtDirectXWidget(pathToModels, pathToMaterials, pathesToShaderSet, parent),
  m_sgo(new StaticGameObject),
  m_pointLightSgo(new StaticGameObject)
{
  this->setWindowTitle("configure point light relative position");
  auto defautPointLightSgo = DependencyResolver::GetPointLightOnMapService()->GetDefaultPointLightSgo();

  m_pointLightSgo->SetModel(GetModel(defautPointLightSgo.modelFileName.toStdString()));
  m_pointLightSgo->SetParent(m_sgo.get());
  
  std::shared_ptr<ConfigurePLRelPosControl> control(new ConfigurePLRelPosControl(this, m_Camera.get(), m_pointLightSgo.get(), mapEditorPreferences));
  m_inputSystem->AddInputListener(control);
}


ConfigurePLRelativePosWidget::~ConfigurePLRelativePosWidget()
{
  
}

void ConfigurePLRelativePosWidget::SetPointLight(const PointLightDbInfo& pointLight)
{
  if (!pointLight.staticGameObjectId)
    RUNTIME_ERROR("to configure point light relative position widget setted point light wihout static game object");

  m_pointLightId = pointLight.id;
  m_sgo->SetModel(GetModel(pointLight.staticGameObjectDbInfo.modelFileName.toStdString()));

  m_pointLightSgo->SetParent(m_sgo.get());
  m_pointLightSgo->SetPosition(pointLight.relativePosX, pointLight.relativePosY, pointLight.relativePosZ);

  GEMath::LookToObjectFromWorldFront(m_Camera.get(), m_sgo.get());
}

void ConfigurePLRelativePosWidget::paintEvent(QPaintEvent* pEvent)
{
  XMMATRIX worldMatrix;
  m_sgo->GetWorldMatrix(worldMatrix);
  m_graphicSystem->AddModelToRenderList(*m_sgo->GetModel(), worldMatrix);

  m_pointLightSgo->GetWorldMatrix(worldMatrix);
  m_graphicSystem->AddModelToRenderList(*m_pointLightSgo->GetModel(), worldMatrix);

  QtDirectXWidget::paintEvent(pEvent);
}

void ConfigurePLRelativePosWidget::EmitPointLightPositionChanged()
{
  XMFLOAT3 position = m_pointLightSgo->GetPosition();
  emit PointLightPositionChanged(m_pointLightId, position.x, position.y, position.z);
}

void ConfigurePLRelativePosWidget::CheckPointLightPosChanged(const PointLightDbInfo& pointLight)
{
  if (m_pointLightId == pointLight.id)
  {
    m_pointLightSgo->SetPosition(pointLight.relativePosX, pointLight.relativePosY, pointLight.relativePosZ);
  }
}