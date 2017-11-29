#include "MapEditor.h"

MapEditor::MapEditor(MapEditorPreferences* mapEditorPreferences, SGOOnMapTableWidget* sgoOnMapTableWidget, QString pathToModels, QString pathToMaterials, QWidget *parent)
  : QtDirectXWidget(pathToModels, pathToMaterials, parent)
{
  this->setWindowFlags(Qt::Sheet | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::CustomizeWindowHint);
  this->setWindowTitle("Map editor");
  m_Camera->SetPosition(-500.0f, 0.0f, 0.0f);
  m_Camera->SetRotation(0.0f, 0.0f, 0.0f);
  m_lightininigSystem->SetAmbientColor(0.5f, 0.5f, 0.5f, 0.5f);
  //m_lightininigSystem->SetDirectLightDirection(0.0f, -1.0f, 1.0f);
  MapEditorControl* mapEditorControl = new MapEditorControl(mapEditorPreferences, sgoOnMapTableWidget, m_Camera.get(), &m_staticGameObjectMap);
  mapEditorControl->SetSelectedObjectIds(&m_selectedObjectIds);
  m_inputSystem->AddInputListener(mapEditorControl);
}

MapEditor::~MapEditor()
{
}

void MapEditor::AddSGOHelper(SGOOnMapDbInfo& sgoOnMap)
{
  StaticGameObject sgo;
  sgo.SetModel(GetModel(sgoOnMap.staticGameObjectDbInfo.modelFileName.toStdString()));
  sgo.GetModel()->GetBoundingBox()->InitializeBuffers(m_graphicSystem->GetDevice());
  sgo.SetPosition(sgoOnMap.xPos, sgoOnMap.yPos, sgoOnMap.zPos);
  sgo.SetRotation(sgoOnMap.xRotate, sgoOnMap.yRotate, sgoOnMap.zRotate);
  sgo.m_SGODbInfoId = sgoOnMap.staticGameObjectDbInfo.id;
  m_staticGameObjectMap[sgoOnMap.id] = sgo;
}

void MapEditor::AddSGO(SGOOnMapDbInfo& sgoOnMap)
{
  AddSGOHelper(sgoOnMap);
  m_octoTree.AddSgo(sgoOnMap.id, &m_staticGameObjectMap[sgoOnMap.id]);
}

void MapEditor::InitializeOctoTree(std::vector<SGOOnMapDbInfo>& gameObjects)
{
  for (auto& sgo : gameObjects)
  {
    AddSGOHelper(sgo);
  }

  std::map<int, StaticGameObject*> test;
  for (auto& sgo : m_staticGameObjectMap)
  {
    test[sgo.first] = &(sgo.second);
  }
  m_octoTree.Initialize(&test, XMFLOAT3(0.0f, 0.0f, 0.0f), 32768);
}

void MapEditor::paintEvent(QPaintEvent* pEvent)
{
  XMMATRIX worldMatrix;
  
  if (m_Camera->NeedRebuildFrustrum())
  {
    m_visibleSgos.clear();
    m_octoTree.GetVisibleSgo(m_Camera->GetCameraFrustrum(), &m_visibleSgos);
  }
 
  for (auto sgo : m_visibleSgos)
  {
    sgo->GetWorldMatrix(worldMatrix);
    m_graphicSystem->AddModelToRenderList(sgo->GetModel(), worldMatrix);
  }

  for (int selectedId : m_selectedObjectIds)
  {
    m_staticGameObjectMap[selectedId].GetWorldMatrix(worldMatrix);
    m_graphicSystem->AddGridToRenderList(m_staticGameObjectMap[selectedId].GetModel()->GetBoundingBox(), worldMatrix);
  }

  static int counter = 0;
  if (counter > 180)
  {
    m_octoTree.DeleteUnusedNodes();
    counter = 0;
  }
  ++counter;
 /* m_octoTree.InitializeAllBBs(m_graphicSystem->GetDevice()); //можно показывать для визуальной отладки окто дерева
  if (m_octoTree.AllBBs.size() > 0)
  {
    for (auto& bb : m_octoTree.AllBBs)
      m_graphicSystem->AddGridToRenderList(bb, XMMatrixIdentity());
  }*/
  
  QtDirectXWidget::paintEvent(pEvent);
}

void MapEditor::DeleteSGO(int id)
{
  m_octoTree.DeleteSgo(id, &m_staticGameObjectMap[id]);
  m_selectedObjectIds.erase(id);
  m_staticGameObjectMap.erase(id);
}

void MapEditor::EditSGO(SGOOnMapDbInfo& sgoOnMap)
{
  AddSGOHelper(sgoOnMap);
  m_octoTree.ObjectChangedPosition(sgoOnMap.id, &m_staticGameObjectMap[sgoOnMap.id]);
}

void MapEditor::SGODbInfoDeleted(int sgoDbInfoId)
{
  for (auto it = m_staticGameObjectMap.begin(), itEnd = m_staticGameObjectMap.end(); it != itEnd;)
  {
    if (it->second.m_SGODbInfoId == sgoDbInfoId)
    {
      m_octoTree.DeleteSgo(it->first, &m_staticGameObjectMap[it->first]);
      m_selectedObjectIds.erase(it->first);
      it = m_staticGameObjectMap.erase(it);
    }
    else
    {
      ++it;
    }
      
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