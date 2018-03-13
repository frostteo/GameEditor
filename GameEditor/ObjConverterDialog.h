#pragma once

#include <QDialog>
#include <qfiledialog.h>
#include "ui_ObjConverterDialog.h"

class ObjMeshConverter;
class MtlMatLibConverter;

class ObjConverterDialog : public QDialog, public Ui::ObjConverterDialog
{
    Q_OBJECT
private slots:
    void on_selectObjFileBtn_clicked();
protected:
  const std::string m_pathToObjModels;
  const std::string m_pathToGEModels;
  const std::string m_pathToGEMaterials;
public:
  ObjConverterDialog(const std::string& pathToObjModels, const std::string& pathToGEModels, const std::string& pathTOGEMaterials, QWidget *parent = Q_NULLPTR);
  ~ObjConverterDialog() = default;
  void done(int result) override;
};
