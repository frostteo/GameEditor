#include "MapEditorPreferencesDialog.h"

MapEditorPreferencesDialog::MapEditorPreferencesDialog(QWidget *parent)
  : QDialog(parent)
{
    setupUi(this);
    connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(this->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    this->setWindowFlags(Qt::Tool | Qt::MSWindowsFixedSizeDialogHint);

    double infinity = INT_MAX;
    double smalestGreaterThenZero = 0.01;

    auto validator = new QDoubleValidator(smalestGreaterThenZero, infinity, 2);
    validator->setLocale(QLocale::English);

    this->objectMoveTxt->setValidator(validator);
    this->objectRotationTxt->setValidator(validator);
    this->cameraZoomTxt->setValidator(validator);
    this->cameraRotationTxt->setValidator(validator);
    this->cameraPanTxt->setValidator(validator);
    this->gridSnapTxt->setValidator(validator);
    this->angleSnapTxt->setValidator(validator);
}

MapEditorPreferencesDialog::~MapEditorPreferencesDialog()
{
}

void MapEditorPreferencesDialog::SetMapEditorPreferences(MapEditorPreferences* mapEditorPreferences)
{
  m_mapEditorPreferences = mapEditorPreferences;
  this->objectMoveTxt->setText(QString::number(m_mapEditorPreferences->GetObjectMoveSpeed()));
  this->objectRotationTxt->setText(QString::number(m_mapEditorPreferences->GetObjectRotationSpeed()));
  this->cameraRotationTxt->setText(QString::number(m_mapEditorPreferences->GetCameraRotationSpeed()));
  this->cameraZoomTxt->setText(QString::number(m_mapEditorPreferences->GetCameraZoomSpeed()));
  this->cameraPanTxt->setText(QString::number(m_mapEditorPreferences->GetCameraPanSpeed()));
  this->gridSnapTxt->setText(QString::number(m_mapEditorPreferences->GetGridSnapSize()));
  this->angleSnapTxt->setText(QString::number(m_mapEditorPreferences->GetAngleSnap()));
  this->useAngleCheckBox->setChecked(m_mapEditorPreferences->GetSnapToAngleState());
  this->useGridCheckBox->setChecked(m_mapEditorPreferences->GetSnapToGridState());
}

void MapEditorPreferencesDialog::done(int result)
{
  if (result == QDialog::Accepted)
  {
    m_mapEditorPreferences->SetObjectRotationSpeed(this->objectRotationTxt->text().toFloat());
    m_mapEditorPreferences->SetObjectMoveSpeed(this->objectMoveTxt->text().toFloat());
    m_mapEditorPreferences->SetCameraRotationSpeed(this->cameraRotationTxt->text().toFloat());
    m_mapEditorPreferences->SetCameraZoomSpeed(this->cameraZoomTxt->text().toFloat());
    m_mapEditorPreferences->SetCameraPanSpeed(this->cameraPanTxt->text().toFloat());
    m_mapEditorPreferences->SetAngleSnap(this->angleSnapTxt->text().toFloat());
    m_mapEditorPreferences->SetGridSnapSize(this->gridSnapTxt->text().toFloat());
    m_mapEditorPreferences->SetSnapToAngleState(this->useAngleCheckBox->isChecked());
    m_mapEditorPreferences->SetSnapToGridState(this->useGridCheckBox->isChecked());
      QDialog::done(result);
  }
  else
  {
    QDialog::done(result);
  }
}