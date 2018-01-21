#include "GameEditor.h"

GameEditor::GameEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    BLLDependencyResolver::GetUnitOfWork()->Initialize(m_hostName, m_databaseName, m_connectionName);
    this->configureUI();
}

void GameEditor::configureUI()
{
  m_mapEditorPreferences = std::unique_ptr<MapEditorPreferences>(new MapEditorPreferences);
  this->ui.actionSnap_to_angle->setChecked(m_mapEditorPreferences->GetSnapToAngleState());
  this->ui.actionSnap_to_grid->setChecked(m_mapEditorPreferences->GetSnapToGridState());
  this->ui.actionUseTestLightining->setChecked(m_mapEditorPreferences->GetUseTestLightiningFlag());

  m_mapEditor = std::unique_ptr<MapEditor>(new MapEditor(m_mapEditorPreferences.get(), m_pathToModels, m_pathToMaterials, this));
  m_mapEditor->show();

  m_SGOTableWidget = std::unique_ptr<SGOTableWidget>(new SGOTableWidget(m_mapEditorPreferences.get(), m_pathToModels, m_pathToMaterials, this));
  m_pointLightTableWidget = std::unique_ptr<PointLightTableWidget>(new PointLightTableWidget(m_mapEditorPreferences.get(), m_pathToModels, m_pathToMaterials, this));
  ui.tabWidget->clear();
  ui.tabWidget->addTab(m_SGOTableWidget.get(), "static game objects"); 
  ui.tabWidget->addTab(m_pointLightTableWidget.get(), "point lights");

  connect(m_SGOTableWidget.get(), SIGNAL(AddToMap(StaticGameObjectDbInfo&)), this, SLOT(AddSGOToMap(StaticGameObjectDbInfo&)));
  connect(m_pointLightTableWidget.get(), SIGNAL(AddToMap(PointLightDbInfo&)), this, SLOT(AddPointLightToMap(PointLightDbInfo&)));

  m_mapEditorData = std::unique_ptr<MapEditorData>(new MapEditorData(m_mapEditor->GetMapEditorControl(), this));
  m_mapEditorData->show();

  connect(m_mapEditor->GetMapEditorControl()->GetMapEditorViewModel()->GetSGOOnMapTM(), SIGNAL(SGOCountChanged(int)), m_SGOTableWidget.get(), SLOT(CountOnMapChanged(int)));
  connect(m_SGOTableWidget.get(), SIGNAL(SGODeleted(int)), (m_mapEditor->GetMapEditorControl()->GetMapEditorViewModel()), SLOT(SGODbInfoDeleted(int)));
  connect(m_SGOTableWidget.get(), SIGNAL(SGOEdited(StaticGameObjectDbInfo&)), (m_mapEditor->GetMapEditorControl()->GetMapEditorViewModel()), SLOT(SGODbInfoEdited(StaticGameObjectDbInfo&)));

  connect(m_SGOTableWidget.get(), SIGNAL(SGOEdited(StaticGameObjectDbInfo&)), m_pointLightTableWidget.get(), SLOT(SGOEditedSlot(StaticGameObjectDbInfo&)));
  connect(m_SGOTableWidget.get(), SIGNAL(BeforeDeleteSgo(int)), m_pointLightTableWidget.get(), SLOT(BeforeDeleteSgo(int)));
  connect(m_SGOTableWidget.get(), SIGNAL(SGODeleted(int)), m_pointLightTableWidget.get(), SLOT(SGODeletedSlot(int)));

  connect(m_mapEditor->GetMapEditorControl()->GetMapEditorViewModel(), SIGNAL(PointLightCountChanged(int)), m_pointLightTableWidget.get(), SLOT(PointLightCountChanged(int)));
  connect(m_pointLightTableWidget.get(), SIGNAL(DeletePointLight(int)), m_mapEditor->GetMapEditorControl()->GetMapEditorViewModel(), SLOT(PointLightDbInfoDeleted(int)));
  connect(m_pointLightTableWidget.get(), SIGNAL(PointLightDbInfoEdited(PointLightDbInfo&)), m_mapEditor->GetMapEditorControl()->GetMapEditorViewModel(), SLOT(PointLightDbInfoEdited(PointLightDbInfo&)));
}

void GameEditor::on_actionObjConverter_triggered()
{
  ObjConverterDialog objConverterDialog;
  objConverterDialog.SetPathToGEModels(m_pathToModels);
  objConverterDialog.SetPathToObjModels(m_pathToObjModels);
  objConverterDialog.SetPathToGEMaterials(m_pathToMaterials.toStdString());

  objConverterDialog.exec();
}

void GameEditor::AddSGOToMap(StaticGameObjectDbInfo& gameObject)
{
  m_mapEditor->GetMapEditorControl()->AddSgoToMap(gameObject);
}

void GameEditor::AddPointLightToMap(PointLightDbInfo& pointLight)
{
  m_mapEditor->GetMapEditorControl()->AddPointLightToMap(pointLight);
}

void GameEditor::show()
{
  QMainWindow::show();
}

void GameEditor::on_editPreferencesAction_triggered()
{
  MapEditorPreferencesDialog dialog;
  dialog.SetMapEditorPreferences(m_mapEditorPreferences.get());
  dialog.exec();
  this->ui.actionSnap_to_angle->setChecked(m_mapEditorPreferences->GetSnapToAngleState());
  this->ui.actionSnap_to_grid->setChecked(m_mapEditorPreferences->GetSnapToGridState());
  this->ui.actionUseTestLightining->setChecked(m_mapEditorPreferences->GetUseTestLightiningFlag());
  m_mapEditor->SetAmbientLight(m_mapEditorPreferences->GetRedAmbientLightColor(), m_mapEditorPreferences->GetGreenAmbientLightColor(), m_mapEditorPreferences->GetBlueAmbientLightColor());
}

void GameEditor::on_actionSnap_to_angle_toggled(bool checked)
{
  m_mapEditorPreferences->SetSnapToAngleState(checked);
}

void GameEditor::on_actionSnap_to_grid_toggled(bool checked)
{
  m_mapEditorPreferences->SetSnapToGridState(checked);
}

void GameEditor::on_actionUseTestLightining_toggled(bool checked)
{
  m_mapEditorPreferences->SetUseTestLightiningFlag(checked);

  if (m_mapEditor)
    m_mapEditor->EnableTestLightining(checked);
}