#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_GameEditor.h"
#include "QtUtils.h"
#include "StaticGameObjectTM.h"
#include "BLLDependencyResolver.h"
#include "AddStaticGameObjectDialog.h"
#include "StaticGameObject.h"

class GameEditor : public QMainWindow
{
    Q_OBJECT
private:
  Ui::GameEditorClass ui;
  std::unique_ptr<StaticGameObjectTM>  m_gameObjectTableModel;
  std::string m_hostName = "hostName";
  std::string m_databaseName = "../GameEditor/database/gameEditor.db";
  std::string m_connectionName = "gameEditorDBConnection";
private:
  void createUI();
private slots:
  void on_addStaticGOBtn_clicked();

public:
    GameEditor(QWidget *parent = Q_NULLPTR);


};
