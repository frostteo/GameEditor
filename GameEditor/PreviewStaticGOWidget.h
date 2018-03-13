#pragma once

#include <QDialog>
#include "ui_PreviewStaticGOWidget.h"
#include <QMessageBox>
#include <memory>
#include "QtDirectXWidget.h"

class GEMath;
class PreviewGameObject;
class StaticGameObject;
class StaticGameObjectDbInfo;
class MapEditorPreferences;
class PathesToShaderSet;

class PreviewStaticGOWidget : public QtDirectXWidget, public Ui::PreviewStaticGOWidget
{
    Q_OBJECT
private:
  MapEditorPreferences* m_mapEditorPreferences;
  std::unique_ptr<StaticGameObject> m_sgo;
protected:
  virtual void paintEvent(QPaintEvent* pEvent) override;
public:
  PreviewStaticGOWidget(
    MapEditorPreferences* mapEditorPreferences,
    const std::string& pathToModels,
    const std::string& pathToMaterials,
    const PathesToShaderSet& pathesToShaderSet,
    QWidget *parent = Q_NULLPTR
    );

  ~PreviewStaticGOWidget();

  bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
  void SetStaticGameObject(const StaticGameObjectDbInfo& staticGameObject);
};
