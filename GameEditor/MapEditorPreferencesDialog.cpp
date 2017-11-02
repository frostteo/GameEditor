#include "MapEditorPreferencesDialog.h"

MapEditorPreferencesDialog::MapEditorPreferencesDialog(QWidget *parent)
  : QDialog(parent)
{
    setupUi(this);
    connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(this->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    this->setWindowFlags(Qt::Tool | Qt::MSWindowsFixedSizeDialogHint);

    double infinity = 2147483647;
    double smalestGreaterThenZero = 0.01;

    auto validator = new QDoubleValidator(smalestGreaterThenZero, infinity, 2);
    validator->setLocale(QLocale::English);

    this->objectMoveTxt->setValidator(validator);
    this->objectRotationTxt->setValidator(validator);
    this->cameraZoomTxt->setValidator(validator);
    this->cameraRotationTxt->setValidator(validator);
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
}

void MapEditorPreferencesDialog::done(int result)
{
  if (result == QDialog::Accepted)
  {
    m_mapEditorPreferences->SetObjectRotationSpeed(this->objectRotationTxt->text().toFloat());
    m_mapEditorPreferences->SetObjectMoveSpeed(this->objectMoveTxt->text().toFloat());
    m_mapEditorPreferences->SetCameraRotationSpeed(this->cameraRotationTxt->text().toFloat());
    m_mapEditorPreferences->SetCameraZoomSpeed(this->cameraZoomTxt->text().toFloat());
      QDialog::done(result);
  }
  else
  {
    QDialog::done(result);
  }
}