#pragma once

#include "QtDirectXWidget.h"
#include "ConfigurePLRelPosControl.h"
#include "PointLightDbInfo.h"

class ConfigurePLRelativePosWidget :
  public QtDirectXWidget
{
  Q_OBJECT
private:
  static const std::string pointLightSgoModel;

  MapEditorPreferences* m_mapEditorPreferences;
  StaticGameObject m_sgo;
  StaticGameObject m_pointLightSgo;
  ConfigurePLRelPosControl* m_control;

  int m_pointLightId;
protected:
  virtual void paintEvent(QPaintEvent* pEvent) override;
public:
  ConfigurePLRelativePosWidget(MapEditorPreferences* mapEditorPreferences, QString pathToModels, QString pathToMaterials, QWidget *parent = Q_NULLPTR);
  virtual ~ConfigurePLRelativePosWidget();
  void SetPointLight(PointLightDbInfo& pointLight);
  void CheckPointLightPosChanged(PointLightDbInfo& pointLight);
  void EmitPointLightPositionChanged();
signals:
  void PointLightPositionChanged(int id, float x, float y, float z);
};

