#pragma once

#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include "ui_AddStaticGameObjectDialog.h"
#include "QtUtils.h"
#include "StaticGameObjectDbInfo.h"

class AddStaticGameObjectDialog : public QDialog, public Ui::AddStaticGameObjectDialog
{
    Q_OBJECT
private slots:
    void on_chooseModelFileBtn_clicked();
protected:
  QString m_pathToModels;
  QString m_pathToMaterials;
  StaticGameObjectDbInfo m_gameObject;
public:
    void done(int result) override;
    AddStaticGameObjectDialog(QWidget *parent = Q_NULLPTR);
    ~AddStaticGameObjectDialog();
    void SetStaticGameObject(StaticGameObjectDbInfo gameObject);
    StaticGameObjectDbInfo GetStaticGameObject();
    void SetPathToModels(QString pathToModels) { m_pathToModels = pathToModels; }
    void SetPathToMaterials(QString pathToMaterials) { m_pathToMaterials = pathToMaterials; }
};
