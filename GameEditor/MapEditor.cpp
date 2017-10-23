#include "MapEditor.h"

MapEditor::MapEditor(QString pathToModels, QString pathToMaterials, QWidget *parent)
  : QtDirectXWidget(pathToModels, pathToMaterials, parent)
{
  this->setWindowFlags(Qt::Sheet | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::CustomizeWindowHint);
  this->setWindowTitle("Map editor");
  m_Camera->SetPosition(0.0f, 0.0f, -500.0f);

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
  sgo.m_SGODbInfoId = sgoOnMap.staticGameObjectDbInfo.id;
  //TODO FHolod: later add rotate data
  m_staticGameObjectMap[sgoOnMap.id] = sgo;
}

void MapEditor::paintEvent(QPaintEvent* pEvent)
{
  for (auto& sgo : m_staticGameObjectMap)
  {
    XMMATRIX worldMatrix;
    sgo.second.GetWorldMatrix(worldMatrix);
    m_graphicSystem->AddModelToRenderList(sgo.second.GetModel(), worldMatrix);
  }
  QtDirectXWidget::paintEvent(pEvent);
}

void MapEditor::DeleteSGO(int id)
{
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