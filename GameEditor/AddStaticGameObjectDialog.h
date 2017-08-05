#pragma once

#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include "ui_AddStaticGameObjectDialog.h"
#include "QtUtils.h"
#include "StaticGameObject.h"

class AddStaticGameObjectDialog : public QDialog, public Ui::AddStaticGameObjectDialog
{
    Q_OBJECT
private slots:
    void on_chooseModelFileBtn_clicked();
    void on_chooseMaterialFileBtn_clicked();
protected:
  QString m_pathToModels;
  QString m_pathToMaterials;
  StaticGameObject m_gameObject;
public:
    void done(int result) override;
    AddStaticGameObjectDialog(QWidget *parent = Q_NULLPTR);
    ~AddStaticGameObjectDialog();
    void SetStaticGameObject(StaticGameObject gameObject);
    StaticGameObject GetStaticGameObject();
    void SetPathToModels(QString pathToModels) { m_pathToModels = pathToModels; }
    void SetPathToMaterials(QString pathToMaterials) { m_pathToMaterials = pathToMaterials; }
};
