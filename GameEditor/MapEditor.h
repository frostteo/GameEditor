#pragma once

#include <QWidget>
#include <memory>
#include "ui_MapEditor.h"
#include "QtDirectXWidget.h"
#include "MapEditorControl.h"

class PointLightVolumeGridObject;
class UnfrozenDrawableBBFactory;
class FrozenDrawableBBFactory;
class GridObject;
class MapEditorViewModel;
class PathesToShaderSet;

class MapEditor : public QtDirectXWidget, public Ui::MapEditor
{
    Q_OBJECT
protected:
  std::vector<StaticGameObject*> m_visibleSgos;
  std::vector<StaticGameObject*> m_selectedSgos;

  std::unique_ptr<PointLightVolumeGridObject> m_pointLightVolumeGridObject;

  std::unique_ptr<UnfrozenDrawableBBFactory> m_unfrozedDrawableBBFactory;
  std::unique_ptr<FrozenDrawableBBFactory> m_frozedDrawableBBFactory;

  std::unique_ptr<MapEditorViewModel> m_mapEditorViewModel;
  std::shared_ptr<MapEditorControl> m_mapEditorControl;
 
  bool m_testLightiningEnabled = true;
  bool m_radiusOfAddingLightSourcesToRenderChanged = true;
protected:
  virtual void paintEvent(QPaintEvent* pEvent) override;
  const GridObject* GetSGODrawableBB(const std::string& modelName, bool isFrozen);
public:
  MapEditor(
    MapEditorPreferences* mapEditorPreferences,
    const std::string& pathToModels,
    const std::string& pathToMaterials, 
    const PathesToShaderSet& pathesToShaderSet,
    QWidget *parent = Q_NULLPTR
    );

  ~MapEditor();
  std::shared_ptr<MapEditorControl> GetMapEditorControl() { return m_mapEditorControl; }
  void EnableTestLightining(bool testLightining);
  void SetAmbientLight(float red, float green, float blue);
  void RadiusOfAddingLightSourcesToRenderChanged() { m_radiusOfAddingLightSourcesToRenderChanged = true; }
};
