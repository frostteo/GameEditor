#pragma once

#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include "ui_AddStaticGameObjectDialog.h"
#include "QtUtils.h"

class AddStaticGameObjectDialog : public QDialog, public Ui::AddStaticGameObjectDialog
{
    Q_OBJECT
private slots:
    void on_chooseModelFileBtn_clicked();
    void on_chooseMaterialFileBtn_clicked();
protected:
  const QString m_pathToModels = "../GameEditor/models";
  const QString m_pathToMaterials = "../GameEditor/materials";
public:
    void done(int result) override;
    AddStaticGameObjectDialog(QWidget *parent = Q_NULLPTR);
    ~AddStaticGameObjectDialog();
};
