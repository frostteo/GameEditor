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

class GameEditor : public QMainWindow
{
    Q_OBJECT
private:
  Ui::GameEditorClass ui;
  std::unique_ptr<StaticGameObjectTM>  m_gameObjectTableModel;
  std::string m_hostName = "hostName";
  std::string m_databaseName = "../GameEditor/database/gameEditor.db";
  std::string m_connectionName = "gameEditorDBConnection";
  QString m_pathToModels = "../GameEditor/models";
  QString m_pathToMaterials = "../GameEditor/materials";
  QString m_pathToObjModels = "../GameEditor/obj models";

  std::map<int, std::string> m_SGOTableOrderFieldMap;
  std::map<int, std::string> m_SGOTableOnPageCountMap;
private:
  void createUI();
  void StaticGameObjectBtnsStateConfigure();
  void fillComboBoxFromMap(QComboBox* comboBox, std::map<int, std::string>& map);
private slots:
  void on_addStaticGOBtn_clicked();
  void on_editStaticGOBtn_clicked();
  void on_deleteStaticGOBtn_clicked();
  void on_previewStaticGOBtn_clicked();
  void staticGameObjectTableRowSelected(const QItemSelection& selected, const QItemSelection& deselected);
  void on_actionObjConverter_triggered();

  void on_SGOTableFirstPageBtn_clicked();
  void on_SGOTablePrevPageBtn_clicked();
  void on_SGOTableNextBtn_clicked();
  void on_SGOTableLastBtn_clicked();
  void on_SGOTablePageTxt_editingFinished();
  void on_SGOTableOrdrerDir_currentIndexChanged(int index);
  void on_SGOTableSortField_currentIndexChanged(int index);
  void on_SGOTableOnPage_currentIndexChanged(int index);

  void on_filterSGONameTxt_editingFinished();
  void on_filterSGOModelTxt_editingFinished();
  void on_filterSGOMaterialTxt_editingFinished();
protected:
  void updateSGOTable();
  void updateSGOTablePagingInfo();
public:
    GameEditor(QWidget *parent = Q_NULLPTR);
    ~GameEditor() { }
};
