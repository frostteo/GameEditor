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

    auto moveRotateValidator = new QDoubleValidator(smalestGreaterThenZero, infinity, 2);
    moveRotateValidator->setLocale(QLocale::English);

    auto colorValidator = new QDoubleValidator(0, 1, 6);
    colorValidator->setLocale(QLocale::English);

    auto testDirectLightDirectionValidator = new QDoubleValidator(INT_MIN, INT_MAX, 2);
    testDirectLightDirectionValidator->setLocale(QLocale::English);

    this->objectMoveTxt->setValidator(moveRotateValidator);
    this->objectRotationTxt->setValidator(moveRotateValidator);
    this->cameraZoomTxt->setValidator(moveRotateValidator);
    this->cameraRotationTxt->setValidator(moveRotateValidator);
    this->cameraPanTxt->setValidator(moveRotateValidator);
    this->gridSnapTxt->setValidator(moveRotateValidator);
    this->angleSnapTxt->setValidator(moveRotateValidator);

    this->redAmbientColorTxt->setValidator(colorValidator);
    this->greenAmbientColorTxt->setValidator(colorValidator);
    this->blueAmbientColorTxt->setValidator(colorValidator);

    this->redDirectLightColorTxt->setValidator(colorValidator);
    this->greenDirectLightColorTxt->setValidator(colorValidator);
    this->blueDirectLightColorTxt->setValidator(colorValidator);

    this->xDirectLightDirTxt->setValidator(testDirectLightDirectionValidator);
    this->yDirectLightDirTxt->setValidator(testDirectLightDirectionValidator);
    this->zDirectLightDirTxt->setValidator(testDirectLightDirectionValidator);
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

  this->redAmbientColorTxt->setText(QString::number(m_mapEditorPreferences->GetRedAmbientTestLightColor()));
  this->greenAmbientColorTxt->setText(QString::number(m_mapEditorPreferences->GetGreenAmbientTestLightColor()));
  this->blueAmbientColorTxt->setText(QString::number(m_mapEditorPreferences->GetBlueAmbientTestLightColor()));

  this->redDirectLightColorTxt->setText(QString::number(m_mapEditorPreferences->GetRedDirectTestLightColor()));
  this->greenDirectLightColorTxt->setText(QString::number(m_mapEditorPreferences->GetGreenDirectTestLightColor()));
  this->blueDirectLightColorTxt->setText(QString::number(m_mapEditorPreferences->GetBlueDirectTestLightColor()));

  this->xDirectLightDirTxt->setText(QString::number(m_mapEditorPreferences->GetXDirectTestLightDirection()));
  this->yDirectLightDirTxt->setText(QString::number(m_mapEditorPreferences->GetYDirectTestLightDirection()));
  this->zDirectLightDirTxt->setText(QString::number(m_mapEditorPreferences->GetZDirectTestLightDirection()));

  this->useTestLightiningCheckBox->setChecked(m_mapEditorPreferences->GetUseTestLightiningFlag());
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

    m_mapEditorPreferences->SetAmbientTestLightColor(this->redAmbientColorTxt->text().toFloat(), this->greenAmbientColorTxt->text().toFloat(), this->blueAmbientColorTxt->text().toFloat());
    m_mapEditorPreferences->SetDirectTestLightColor(this->redDirectLightColorTxt->text().toFloat(), this->greenDirectLightColorTxt->text().toFloat(), this->blueDirectLightColorTxt->text().toFloat());
    m_mapEditorPreferences->SetDirectTestLightDirection(this->xDirectLightDirTxt->text().toFloat(), this->yDirectLightDirTxt->text().toFloat(), this->zDirectLightDirTxt->text().toFloat());
    m_mapEditorPreferences->SetUseTestLightiningFlag(this->useTestLightiningCheckBox->isChecked());

    QDialog::done(result);
  }
  else
  {
    QDialog::done(result);
  }
}