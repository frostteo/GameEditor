#pragma once

#include <QWidget>
#include "ui_MapEditor.h"
#include "QtDirectXWidget.h"
#include <map>
#include "StaticGameObject.h"
#include "MapEditorControl.h"
#include "SGOOnMapTM.h"
#include <set>

class MapEditor : public QtDirectXWidget, public Ui::MapEditor
{
    Q_OBJECT
protected:
  std::map<int, StaticGameObject> m_staticGameObjectMap;
  std::set<int> m_selectedObjectIds;
protected:
  virtual void paintEvent(QPaintEvent* pEvent) override;
public:
  MapEditor(MapEditorPreferences* mapEditorPreferences, SGOOnMapTableWidget* sgoOnMapTableWidget, QString pathToModels, QString pathToMaterials, QWidget *parent = Q_NULLPTR);
  ~MapEditor();
public slots:
  void AddSGO(SGOOnMapDbInfo& sgoOnMap);
  void DeleteSGO(int id);
  void EditSGO(SGOOnMapDbInfo& sgoOnMap);
  void SGODbInfoDeleted(int sgoDbInfoId);
  void SGODbInfoEdited(StaticGameObjectDbInfo& dbInfo);
  void SetSelectedObjectObjectId(int selectedObjectId) { m_selectedObjectIds.clear(); m_selectedObjectIds.insert(selectedObjectId); }
};
