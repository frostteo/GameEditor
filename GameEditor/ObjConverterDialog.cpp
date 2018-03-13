#include "ObjConverterDialog.h"
#include "ObjMeshConverter.h"
#include "MtlMatLibConverter.h"

ObjConverterDialog::ObjConverterDialog(
  const std::string& pathToObjModels, 
  const std::string& pathToGEModels, 
  const std::string& pathTOGEMaterials,
  QWidget *parent
  )
    : QDialog(parent),
    m_pathToObjModels(pathToObjModels),
    m_pathToGEModels(pathToGEModels),
    m_pathToGEMaterials(pathTOGEMaterials)
{
  setupUi(this);
}

void ObjConverterDialog::on_selectObjFileBtn_clicked()
{
  QString objModelFileName = QFileDialog::getOpenFileName(this,
    tr("Open obj model file name"), QString::fromStdString(m_pathToObjModels), tr("Obj Files (*.obj)"));

  this->objFileNameTxt->setText(objModelFileName);
}

void ObjConverterDialog::done(int result)
{
  if (result == QDialog::Accepted)  // ok was pressed
  {
    QString errorMsg = "";
    std::string mtlLibFileName;
    std::string objectModelFileName;
    std::string txtModelFileName;

    std::string modelNameFromDialog = this->objFileNameTxt->text().trimmed().toStdString();

    bool objFileNameIsEmpty = modelNameFromDialog.empty();

    if (objFileNameIsEmpty)
      errorMsg += tr("Object file name must be defined\n");

    if (!objFileNameIsEmpty)
    {
      mtlLibFileName = FileProcessor::GetFileNameWithoutExtension(modelNameFromDialog) + MtlMatLibConverter::MTL_MAT_EXT;
      if (!FileProcessor::FileExists(mtlLibFileName))
        errorMsg += tr(".mtl material library with same name as object file must be in directory\n");
    }

    if (this->meshFileNameTxt->text().trimmed().isEmpty())
      errorMsg += tr("Game editor mesh file name must be defined\n");

    this->errorsMsg->setText(errorMsg);

    if (this->errorsMsg->text().isEmpty()){
      ObjMeshConverter objConverter;
      MtlMatLibConverter mtlMatLibConverter(m_pathToGEMaterials);

      objectModelFileName = this->objFileNameTxt->text().toStdString();
      txtModelFileName = m_pathToGEModels + FileProcessor::FILE_SEPARATOR + this->meshFileNameTxt->text().toStdString() + ".txt";

      objConverter.ConvertModel(objectModelFileName, txtModelFileName);
      mtlMatLibConverter.ConvertMtlMaterials(mtlLibFileName, this->needReplaceMaterialIfExistsFlag->isChecked());

      QDialog::done(result);
    }
      
  }
  else
  {
    QDialog::done(result);
  }
}