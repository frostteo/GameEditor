#pragma once

#include <QDialog>
#include <qfiledialog.h>
#include "ui_ObjConverterDialog.h"
#include "QtUtils.h"
#include "ObjMeshConverter.h"

class ObjConverterDialog : public QDialog, public Ui::ObjConverterDialog
{
    Q_OBJECT
private slots:
    void on_selectObjFileBtn_clicked();
protected:
  QString m_pathToObjModels;
  QString m_pathToGEModels;
public:
    ObjConverterDialog(QWidget *parent = Q_NULLPTR);
    ~ObjConverterDialog();
    void SetPathToGEModels(QString pathToGEModels) { m_pathToGEModels = pathToGEModels; }
    void SetPathToObjModels(QString pathToObjModels) { m_pathToObjModels = pathToObjModels; }
    void done(int result) override;
};
