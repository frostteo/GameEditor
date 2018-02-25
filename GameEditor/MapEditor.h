#pragma once

#include <QWidget>
#include <memory>
#include "ui_MapEditor.h"
#include "QtDirectXWidget.h"
#include "MapEditorViewModel.h"
#include "MapEditorControl.h"
#include "PointLightVolumeGridObject.h"

class MapEditor : public QtDirectXWidget, public Ui::MapEditor
{
    Q_OBJECT
protected:
  MapEditorControl* m_mapEditorControl;
  std::unique_ptr<MapEditorViewModel> m_mapEditorViewModel;
  std::vector<StaticGameObject*> m_visibleSgos;
  std::vector<StaticGameObject*> m_selectedSgos;
  bool m_testLightiningEnabled = true;
  PointLightVolumeGridObject m_pointLightVolumeGridObject;
  bool m_radiusOfAddingLightSourcesToRenderChanged = true;
protected:
  virtual void paintEvent(QPaintEvent* pEvent) override;
public:
  MapEditor(MapEditorPreferences* mapEditorPreferences, QString pathToModels, QString pathToMaterials, QWidget *parent = Q_NULLPTR);
  ~MapEditor();
  MapEditorControl* GetMapEditorControl() { return m_mapEditorControl; }
  void EnableTestLightining(bool testLightining);
  void SetAmbientLight(float red, float green, float blue);
  void RadiusOfAddingLightSourcesToRenderChanged() { m_radiusOfAddingLightSourcesToRenderChanged = true; }
};
