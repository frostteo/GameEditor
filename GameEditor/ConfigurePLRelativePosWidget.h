#pragma once

#include <memory>
#include <string>
#include <QWidget>
#include "QtDirectXWidget.h"

class ConfigurePLRelPosControl;
class DependencyResolver;
class PointLightDbInfo;
class StaticGameObject;
class MapEditorPreferences;
class PathesToShaderSet;

class ConfigurePLRelativePosWidget :
  public QtDirectXWidget
{
  Q_OBJECT
private:
  std::unique_ptr<StaticGameObject> m_sgo;
  std::unique_ptr<StaticGameObject> m_pointLightSgo;
  int m_pointLightId;
protected:
  virtual void paintEvent(QPaintEvent* pEvent) override;
public:
  ConfigurePLRelativePosWidget(
    MapEditorPreferences* mapEditorPreferences,
    const std::string& pathToModels,
    const std::string& pathToMaterials,
    const PathesToShaderSet& pathesToShaderSet, 
    QWidget *parent = Q_NULLPTR
    );

  virtual ~ConfigurePLRelativePosWidget();
  void SetPointLight(const PointLightDbInfo& pointLight);
  void CheckPointLightPosChanged(const PointLightDbInfo& pointLight);
  void EmitPointLightPositionChanged();
signals:
  void PointLightPositionChanged(int id, float x, float y, float z);
};

