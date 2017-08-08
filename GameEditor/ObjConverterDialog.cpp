#include "ObjConverterDialog.h"

ObjConverterDialog::ObjConverterDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
}

ObjConverterDialog::~ObjConverterDialog()
{
}

void ObjConverterDialog::on_selectObjFileBtn_clicked()
{
  QString objModelFileName = QFileDialog::getOpenFileName(this,
    tr("Open obj model file name"), m_pathToObjModels, tr("Obj Files (*.obj)"));

  this->objFileNameTxt->setText(QFileInfo(objModelFileName).fileName());
}

void ObjConverterDialog::done(int result)
{
  if (result == QDialog::Accepted)  // ok was pressed
  {
    QString errorMsg = "";
    if (this->objFileNameTxt->text().trimmed().isEmpty())
      errorMsg += tr("Object file name must be defined\n");

    if (this->meshFileNameTxt->text().trimmed().isEmpty())
      errorMsg += tr("Game editor mesh file name must be defined\n");

    this->errorsMsg->setText(errorMsg);

    if (this->errorsMsg->text().isEmpty()){
      ObjMeshConverter objConverter;
      objConverter.ConvertModel(QtUtils::QStringToStdStr(m_pathToObjModels + QtUtils::fileSeparator + this->objFileNameTxt->text()), QtUtils::QStringToStdStr(m_pathToGEModels + +QtUtils::fileSeparator + this->meshFileNameTxt->text() + ".txt"));

      QDialog::done(result);
    }
      
  }
  else
  {
    QDialog::done(result);
  }
}