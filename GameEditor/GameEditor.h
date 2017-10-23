#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QAction>
#include <memory>
#include "ui_GameEditor.h"
#include "QtUtils.h"
#include "ObjConverterDialog.h"
#include "MapEditorData.h"
#include "MapEditor.h"
#include "SGOTableWidget.h"

class GameEditor : public QMainWindow
{
    Q_OBJECT
private:
  Ui::GameEditorClass ui;
  std::string m_hostName = "hostName";
  std::string m_databaseName = "../GameEditor/database/gameEditor.db";
  std::string m_connectionName = "gameEditorDBConnection";
  QString m_pathToModels = "../GameEditor/models";
  QString m_pathToMaterials = "../GameEditor/materials";
  QString m_pathToObjModels = "../GameEditor/obj models";

  std::unique_ptr<SGOTableWidget> m_SGOTableWidget;
  std::unique_ptr<MapEditorData> m_mapEditorData;
  std::unique_ptr<MapEditor> m_mapEditor;
private:
  void configureUI();
private slots:
  void on_actionObjConverter_triggered();
  void AddSGOToMap(StaticGameObjectDbInfo& gameObject);
public:
    GameEditor(QWidget *parent = Q_NULLPTR);
    ~GameEditor() { }
    virtual void show();
};
