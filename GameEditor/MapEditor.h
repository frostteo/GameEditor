#pragma once

#include <QWidget>
#include "ui_MapEditor.h"
#include "QtDirectXWidget.h"
#include "MapEditorViewModel.h"
#include "MapEditorControl.h"

class MapEditor : public QtDirectXWidget, public Ui::MapEditor
{
    Q_OBJECT
protected:
  MapEditorControl* m_mapEditorControl;
  MapEditorViewModel m_mapEditorViewModel;
  std::vector<StaticGameObject*> m_visibleSgos;
  std::vector<StaticGameObject*> m_selectedSgos;
protected:
  virtual void paintEvent(QPaintEvent* pEvent) override;
public:
  MapEditor(MapEditorPreferences* mapEditorPreferences, QString pathToModels, QString pathToMaterials, QWidget *parent = Q_NULLPTR);
  ~MapEditor();
  MapEditorControl* GetMapEditorControl() { return m_mapEditorControl; }
};
