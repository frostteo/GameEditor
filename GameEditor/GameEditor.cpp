#include "GameEditor.h"

GameEditor::GameEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    BLLDependencyResolver::GetUnitOfWork()->Initialize(m_hostName, m_databaseName, m_connectionName);
    this->createUI();
}

void GameEditor::createUI()
{
  m_SGOTableWidget = std::unique_ptr<SGOTableWidget>(new SGOTableWidget(m_pathToModels, m_pathToMaterials));
  ui.tabWidget->clear();
  ui.tabWidget->addTab(m_SGOTableWidget.get(), "static game objects"); 
 

  //this->setStyleSheet(
  //  "QPushButton#SGOTableFirstPageBtn {"
  //  "background-color: red;"
  //  "border-style: outset;"
  //  "border-width: 2px;"
  //  "border-radius: 10px;"
  //  "border-color: beige;"
  //  "font: bold 14px;"
  //  "min-width: 10em;"
  //  "padding: 6px; "
  //  "text-align:left;"
  //  "}"
  //  );

}

void GameEditor::on_actionObjConverter_triggered()
{
  ObjConverterDialog objConverterDialog;
  objConverterDialog.SetPathToGEModels(m_pathToModels);
  objConverterDialog.SetPathToObjModels(m_pathToObjModels);
  objConverterDialog.SetPathToGEMaterials(m_pathToMaterials.toStdString());

  objConverterDialog.exec();
}

void GameEditor::show()
{
  QMainWindow::show();
}