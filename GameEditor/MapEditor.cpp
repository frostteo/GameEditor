#include "MapEditor.h"

MapEditor::MapEditor(MapEditorPreferences* mapEditorPreferences, QString pathToModels, QString pathToMaterials, QWidget *parent)
  : QtDirectXWidget(pathToModels, pathToMaterials, parent)
{
  this->setWindowFlags(Qt::Sheet | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::CustomizeWindowHint);
  this->setWindowTitle("Map editor");
  m_Camera->SetPosition(-500.0f, 0.0f, 0.0f);
  m_Camera->SetRotation(0.0f, 0.0f, 0.0f);

  m_mapEditorViewModel = std::make_unique<MapEditorViewModel>();
  m_mapEditorViewModel->Initialize(pathToModels.toStdString(), m_graphicSystem->GetModelFactory(), mapEditorPreferences);
  m_mapEditorControl = new MapEditorControl(m_mapEditorViewModel.get(), &m_visibleSgos, m_Camera.get());
  m_inputSystem->AddInputListener(m_mapEditorControl);

  EnableTestLightining(mapEditorPreferences->GetUseTestLightiningFlag());
  m_pointLightVolumeGridObject.InitializeBuffers(m_graphicSystem->GetDevice());
  SetAmbientLight(mapEditorPreferences->GetRedAmbientLightColor(), mapEditorPreferences->GetBlueAmbientLightColor(), mapEditorPreferences->GetBlueAmbientLightColor());
}

MapEditor::~MapEditor()
{
}

void MapEditor::paintEvent(QPaintEvent* pEvent)
{
  XMMATRIX worldMatrix;

  m_inputSystem->Frame();

  if (m_Camera->NeedRebuildFrustrum())
  {
    m_mapEditorViewModel->GetVisibleSgo(m_Camera->GetCameraFrustrum(), &m_visibleSgos);
    m_mapEditorViewModel->GetVisiblePointLights(m_Camera->GetCameraFrustrum(), m_lightininigSystem->GetPointLights());
  }
 
  for (auto sgo : m_visibleSgos)
  {
    sgo->GetWorldMatrix(worldMatrix);
    m_graphicSystem->AddModelToRenderList(sgo->GetModel(), worldMatrix);
  }

  m_mapEditorViewModel->GetSelectedSgos(&m_selectedSgos);
  for (auto sgo : m_selectedSgos)
  {
    sgo->GetDrawableBoundingBox()->InitializeBuffers(m_graphicSystem->GetDevice(), sgo->isFrozen);
    sgo->GetWorldMatrix(worldMatrix);
    m_graphicSystem->AddGridToRenderList(sgo->GetDrawableBoundingBox(), worldMatrix);
  }

  static int counter = 0;
  if (counter > 180)
  {
    m_mapEditorViewModel->DeleteUnusedNodesInOctTree();
    counter = 0;
  }
  ++counter;

  if (m_testLightiningEnabled)
  {
    for (auto pointLight : *m_lightininigSystem->GetPointLights())
    {
      pointLight->GetWorldMatrix(worldMatrix);
      m_graphicSystem->AddGridToRenderList(&m_pointLightVolumeGridObject, worldMatrix);
    }
  }
  else
  {

  }

  if (m_testLightiningEnabled)
    m_graphicSystem->Render(m_Camera.get(), m_mapEditorViewModel->GetMapEditorPreferences()->GetTestLightiningSystem());
  else
    m_graphicSystem->RenderDefferedTesselated(m_Camera.get(), m_lightininigSystem.get());

  // trigger another update as soon as possible 
  update();
}

void MapEditor::EnableTestLightining(bool testLightining)
{
  m_testLightiningEnabled = testLightining;

  if (testLightining)
    m_shaderConfiguration->ConfigureForwardRenderer();
  else
    m_shaderConfiguration->ConfigureDefferedRenderer();
}

void MapEditor::SetAmbientLight(float red, float green, float blue)
{
  m_lightininigSystem->SetAmbientColor(red, green, blue, 1.0f);
}