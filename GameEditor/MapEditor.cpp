#include "MapEditor.h"
#include "Camera.h"
#include "LightininigSystem.h"
#include "PointLightVolumeGridObject.h"
#include "UnfrozenDrawableBBFactory.h"
#include "FrozenDrawableBBFactory.h"
#include "MapEditorViewModel.h"
#include "PathesToShaderSet.h"

MapEditor::MapEditor(
  MapEditorPreferences* mapEditorPreferences, 
  const std::string& pathToModels, 
  const std::string& pathToMaterials,
  const PathesToShaderSet& pathesToShaderSet, 
  int width,
  int height,
  QWidget *parent
  )
  : QtDirectXWidget(pathToModels, pathToMaterials, pathesToShaderSet, parent, width, height),
  m_visibleSgos(),
  m_selectedSgos(),
  m_pointLightVolumeGridObject(new PointLightVolumeGridObject(m_graphicSystem->GetDevice())),
  m_unfrozedDrawableBBFactory(new UnfrozenDrawableBBFactory(m_graphicSystem->GetDevice(), m_graphicSystem->GetModelFactory())),
  m_frozedDrawableBBFactory(new FrozenDrawableBBFactory(m_graphicSystem->GetDevice(), m_graphicSystem->GetModelFactory())),
  m_mapEditorViewModel(new MapEditorViewModel(pathToModels, m_graphicSystem->GetModelFactory(), mapEditorPreferences, m_graphicSystem->GetD3dConfigurer())),
  m_mapEditorControl(new MapEditorControl(m_mapEditorViewModel.get(), &m_visibleSgos, m_Camera.get()))
{
  this->setWindowFlags(Qt::Sheet | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::CustomizeWindowHint);
  this->setWindowTitle("Map editor");
  m_Camera->SetPosition(0.0f, 0.0f, -500.0f);
  m_Camera->SetRotation(0.0f, 0.0f, 0.0f);

  m_inputSystem->AddInputListener(m_mapEditorControl);

  EnableTestLightining(mapEditorPreferences->GetUseTestLightiningFlag());

  SetAmbientLight(mapEditorPreferences->GetRedAmbientLightColor(), mapEditorPreferences->GetBlueAmbientLightColor(), mapEditorPreferences->GetBlueAmbientLightColor());
}

MapEditor::~MapEditor()
{
}

void MapEditor::paintEvent(QPaintEvent* pEvent)
{
  XMMATRIX worldMatrix;

  m_inputSystem->Frame();

  if (m_Camera->NeedRebuildFrustrum() || m_mapEditorControl->m_objectsCountInVisibleAreaWasChanged || m_radiusOfAddingLightSourcesToRenderChanged)
  {
    m_mapEditorViewModel->GetVisibleSgo(*m_Camera, &m_visibleSgos);
    m_mapEditorViewModel->GetVisiblePointLights(m_Camera.get(), m_lightininigSystem.get());
    m_mapEditorControl->m_objectsCountInVisibleAreaWasChanged = false;
    m_radiusOfAddingLightSourcesToRenderChanged = false;
  }
 
  for (auto sgo : m_visibleSgos)
  {
    sgo->GetWorldMatrix(worldMatrix);
    m_graphicSystem->AddModelToRenderList(*sgo->GetModel(), worldMatrix, sgo->castShadows);
  }

  m_mapEditorViewModel->GetSelectedSgos(&m_selectedSgos);
  for (auto sgo : m_selectedSgos)
  {
    sgo->GetWorldMatrix(worldMatrix);
    m_graphicSystem->AddGridToRenderList(GetSGODrawableBB(sgo->GetModel()->GetName(), sgo->isFrozen), worldMatrix);
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
    for (auto pointLight : *m_lightininigSystem->GetPointLightsNonCastShadows())
    {
      pointLight->Get20PercentLightVolumeMatrix(worldMatrix);
      m_graphicSystem->AddGridToRenderList(m_pointLightVolumeGridObject.get(), worldMatrix);
    }
    for (auto pointLight : *m_lightininigSystem->GetPointLightsCastShadows())
    {
      pointLight->Get20PercentLightVolumeMatrix(worldMatrix);
      m_graphicSystem->AddGridToRenderList(m_pointLightVolumeGridObject.get(), worldMatrix);
    }
  }
  else
  {

  }

  if (m_testLightiningEnabled)
  {
    m_graphicSystem->Render(m_Camera.get(), m_mapEditorViewModel->GetMapEditorPreferences()->GetTestLightiningSystem());
  }
  else
  {
    if (m_mapEditorViewModel->GetMapEditorPreferences()->GetShowShadows())
      m_graphicSystem->RenderDefferedTesselatedWithShadows(m_Camera.get(), m_lightininigSystem.get());
    else 
      m_graphicSystem->RenderDefferedTesselatedWithoutShadows(m_Camera.get(), m_lightininigSystem.get());
  }

  // trigger another update as soon as possible 
  update();
}

const GridObject* MapEditor::GetSGODrawableBB(const std::string& modelName, bool isFrozen)
{
  if (isFrozen)
    return m_frozedDrawableBBFactory->GetResource(modelName);

  return m_unfrozedDrawableBBFactory->GetResource(modelName);
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