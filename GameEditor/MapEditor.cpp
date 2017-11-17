#include "MapEditor.h"

MapEditor::MapEditor(MapEditorPreferences* mapEditorPreferences, SGOOnMapTM* sgoOnMapTM, QString pathToModels, QString pathToMaterials, QWidget *parent)
  : QtDirectXWidget(pathToModels, pathToMaterials, parent)
{
  this->setWindowFlags(Qt::Sheet | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::CustomizeWindowHint);
  this->setWindowTitle("Map editor");
 /* m_Camera->SetPosition(-500.0f, 0.0f, 0.0f);
  m_Camera->SetRotation(0.0f, 90.0f, 0.0f);*/
  m_Camera->SetPosition(500.0f, 0.0f, 0.0f);
  m_Camera->SetRotation(0.0f, -90.0f, 0.0f);
  MapEditorControl* mapEditorControl = new MapEditorControl(mapEditorPreferences, sgoOnMapTM, m_Camera.get(), &m_staticGameObjectMap);
  mapEditorControl->SetSelectedObjectId(&m_selectedObjectId);
  m_inputSystem->AddInputListener(mapEditorControl);
}

MapEditor::~MapEditor()
{
}

void MapEditor::AddSGO(SGOOnMapDbInfo& sgoOnMap)
{
  StaticGameObject sgo;
  sgo.SetModel(GetModel(sgoOnMap.staticGameObjectDbInfo.modelFileName.toStdString()));
  sgo.GetModel()->GetBoundingBox()->InitializeBuffers(m_graphicSystem->GetDevice());
  sgo.SetPosition(sgoOnMap.xPos, sgoOnMap.yPos, sgoOnMap.zPos);
  sgo.SetRotation(sgoOnMap.xRotate, sgoOnMap.yRotate, sgoOnMap.zRotate);
  sgo.m_SGODbInfoId = sgoOnMap.staticGameObjectDbInfo.id;
  m_staticGameObjectMap[sgoOnMap.id] = sgo;
}

void MapEditor::paintEvent(QPaintEvent* pEvent)
{
  XMMATRIX worldMatrix;

  for (auto& sgo : m_staticGameObjectMap)
  {
    sgo.second.GetWorldMatrix(worldMatrix);
    m_graphicSystem->AddModelToRenderList(sgo.second.GetModel(), worldMatrix);
  }

  if (m_selectedObjectId != MapEditorControl::NOTHING_SELECTED)
  {
    m_staticGameObjectMap[m_selectedObjectId].GetWorldMatrix(worldMatrix);
    m_graphicSystem->AddGridToRenderList(m_staticGameObjectMap[m_selectedObjectId].GetModel()->GetBoundingBox(), worldMatrix);
  }
  QtDirectXWidget::paintEvent(pEvent);
}

void MapEditor::DeleteSGO(int id)
{
  if (m_selectedObjectId == id)
    m_selectedObjectId = MapEditorControl::NOTHING_SELECTED;
  m_staticGameObjectMap.erase(id);
}

void MapEditor::EditSGO(SGOOnMapDbInfo& sgoOnMap)
{
  AddSGO(sgoOnMap);
}

void MapEditor::SGODbInfoDeleted(int sgoDbInfoId)
{
  for (auto it = m_staticGameObjectMap.begin(), itEnd = m_staticGameObjectMap.end(); it != itEnd;)
  {
    if (it->second.m_SGODbInfoId == sgoDbInfoId)
      it = m_staticGameObjectMap.erase(it);
    else
      ++it;
  }
}

void MapEditor::SGODbInfoEdited(StaticGameObjectDbInfo& dbInfo)
{
  for (auto& sgo : m_staticGameObjectMap)
  {
    if (sgo.second.m_SGODbInfoId == dbInfo.id)
    {
      sgo.second.SetModel(GetModel(dbInfo.modelFileName.toStdString()));
      sgo.second.GetModel()->GetBoundingBox()->InitializeBuffers(m_graphicSystem->GetDevice());
    }
  }
}