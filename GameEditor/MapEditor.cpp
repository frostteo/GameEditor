#include "MapEditor.h"

MapEditor::MapEditor(MapEditorPreferences* mapEditorPreferences, QString pathToModels, QString pathToMaterials, QWidget *parent)
  : QtDirectXWidget(pathToModels, pathToMaterials, parent)
{
  this->setWindowFlags(Qt::Sheet | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::CustomizeWindowHint);
  this->setWindowTitle("Map editor");
  m_Camera->SetPosition(-500.0f, 0.0f, 0.0f);
  m_Camera->SetRotation(0.0f, 0.0f, 0.0f);

  m_mapEditorViewModel.Initialize(pathToModels.toStdString(), m_graphicSystem->GetModelFactory(), mapEditorPreferences);
  m_mapEditorControl = new MapEditorControl(&m_mapEditorViewModel, &m_visibleSgos, m_Camera.get());
  m_inputSystem->AddInputListener(m_mapEditorControl);
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
    m_mapEditorViewModel.GetVisibleSgo(m_Camera->GetCameraFrustrum(), &m_visibleSgos);
  }
 
  for (auto sgo : m_visibleSgos)
  {
    sgo->GetWorldMatrix(worldMatrix);
    m_graphicSystem->AddModelToRenderList(sgo->GetModel(), worldMatrix);
  }

  m_mapEditorViewModel.GetSelectedSgos(&m_selectedSgos);
  for (auto sgo : m_selectedSgos)
  {
    sgo->GetDrawableBoundingBox()->InitializeBuffers(m_graphicSystem->GetDevice(), sgo->isFrozen);
    sgo->GetWorldMatrix(worldMatrix);
    m_graphicSystem->AddGridToRenderList(sgo->GetDrawableBoundingBox(), worldMatrix);
  }

  static int counter = 0;
  if (counter > 180)
  {
    m_mapEditorViewModel.DeleteUnusedNodesInOctTree();
    counter = 0;
  }
  ++counter;
 
  m_graphicSystem->Render(m_Camera.get(), m_mapEditorViewModel.GetMapEditorPreferences()->GetTestLightiningSystem());

  // trigger another update as soon as possible 
  update();
}
