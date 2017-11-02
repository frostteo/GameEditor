#pragma once

#include <QWidget>
#include "ui_MapEditor.h"
#include "QtDirectXWidget.h"
#include <map>
#include "StaticGameObject.h"
#include "SGOOnMapDbInfo.h"
#include "MapEditorControl.h"

class MapEditor : public QtDirectXWidget, public Ui::MapEditor
{
    Q_OBJECT
protected:
  std::map<int, StaticGameObject> m_staticGameObjectMap;
  int m_selectedObjectId = MapEditorControl::NOTHING_SELECTED;
protected:
  virtual void paintEvent(QPaintEvent* pEvent) override;
public:
  MapEditor(QString pathToModels, QString pathToMaterials, QWidget *parent = Q_NULLPTR);
  ~MapEditor();
public slots:
  void AddSGO(SGOOnMapDbInfo& sgoOnMap);
  void DeleteSGO(int id);
  void EditSGO(SGOOnMapDbInfo& sgoOnMap);
  void SGODbInfoDeleted(int sgoDbInfoId);
  void SGODbInfoEdited(StaticGameObjectDbInfo& dbInfo);
};
