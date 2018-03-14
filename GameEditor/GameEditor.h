#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QAction>
#include <memory>
#include "ui_GameEditor.h"
#include "MapEditorData.h"
#include "MapEditor.h"
#include "SGOTableWidget.h"
#include "MapEditorPreferencesDialog.h"
#include "MapEditorPreferences.h"
#include "PointLightTableWidget.h"
#include "PathesToShaderSet.h"
#include "ControlDialog.h"

class ObjConverterDialog;

class GameEditor : public QMainWindow
{
    Q_OBJECT
private:
  static const std::string pathesFileName;

  Ui::GameEditorClass ui;
  std::string m_hostName;
  std::string m_databaseName;
  std::string m_connectionName;
  std::string m_pathToModels;
  std::string m_pathToMaterials;
  std::string m_pathToObjModels;
  PathesToShaderSet m_pathesToShaderSet;

  std::unique_ptr<SGOTableWidget> m_SGOTableWidget;
  std::unique_ptr<PointLightTableWidget> m_pointLightTableWidget;
  std::unique_ptr<MapEditorData> m_mapEditorData;
  std::unique_ptr<MapEditor> m_mapEditor;
  std::unique_ptr<MapEditorPreferences> m_mapEditorPreferences;

  std::unique_ptr<ControlDialog> m_controlsDialog;

  float m_oldRadiusOfAddingLightSourcesToRender = 0.0f;
private:
  void configureUI();
  void ReadPathesFromFile();
private slots:
  void on_actionObjConverter_triggered();
  void AddSGOToMap(StaticGameObjectDbInfo& gameObject);
  void AddPointLightToMap(PointLightDbInfo& pointLight);
  void on_editPreferencesAction_triggered();
  void on_actionSnap_to_angle_toggled(bool checked);
  void on_actionSnap_to_grid_toggled(bool checked);
  void on_actionUseTestLightining_toggled(bool checked);
  void on_actionShowShadows_toggled(bool checked);
  void on_actionControl_triggered();
public:
    GameEditor(QWidget *parent = Q_NULLPTR);
    ~GameEditor() { }
    virtual void show();
};
