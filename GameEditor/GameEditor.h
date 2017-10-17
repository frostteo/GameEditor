#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QAction>
#include <memory>
#include "ui_GameEditor.h"
#include "QtUtils.h"
#include "StaticGameObjectTM.h"
#include "BLLDependencyResolver.h"
#include "AddStaticGameObjectDialog.h"
#include "StaticGameObjectDbInfo.h"
#include "PreviewStaticGOWidget.h"
#include "ObjConverterDialog.h"
#include "SGOTableWidget.h"

#include "QtGameFrameworkTest.h"

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
private:
  void createUI();
private slots:
  void on_actionObjConverter_triggered();
public:
    GameEditor(QWidget *parent = Q_NULLPTR);
    ~GameEditor() { }
    virtual void show();
};
