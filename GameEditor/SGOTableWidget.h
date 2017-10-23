#pragma once

#include <memory>
#include <QWidget>
#include <qtableview.h>
#include <qboxlayout.h>
#include "ui_SGOTableWidget.h"
#include "SGOWidgetToolBox.h"
#include "StaticGameObjectTM.h"
#include "AddStaticGameObjectDialog.h"
#include "QtGEPaginator.h"
#include "PreviewStaticGOWidget.h"

class SGOTableWidget : public QWidget
{
    Q_OBJECT
private:
  Ui::SGOTableWidget ui;
  std::unique_ptr<SGOWidgetToolBox> m_SGOToolBox;
  std::unique_ptr<QTableView> m_SGOTable;
  std::unique_ptr<StaticGameObjectTM> m_SGOTableModel;
  std::unique_ptr<QtGEPaginator> m_SGOPaginator;

  QString m_pathToModels;
  QString m_pathToMaterials;
  std::unique_ptr<PreviewStaticGOWidget> m_previewStaticGOWidget;
protected slots:
  void on_addSGOBtn_clicked();
  void on_editSGOBtn_clicked();
  void on_deleteSGOBtn_clicked();
  void editBtnsStateConfigure();
  void SGOtableRowSelected(const QItemSelection& selected, const QItemSelection& deselected);
  void PaginatorPageChanged(int pageNumber, int onPage);
  void HeaderSectionClicked(int sectionIndex);
  
  void on_previewSGOBtn_clicked();
  void on_addToMapBtn_clicked();
  void on_SGODeletedFromMap(int id);
protected:
  void configureTable();
  void configureUI();
  void configurePaginator();
public slots:
  void UpdateTable();
public:
    SGOTableWidget(QString& pathToModels, QString& pathToMaterials, QWidget *parent = Q_NULLPTR);
    ~SGOTableWidget();
    void SetPathToModels(QString& path) { m_pathToModels = path; }
    void SetPathToMaterials(QString& path) { m_pathToMaterials = path; }
    StaticGameObjectTM* GetTableModel() { return m_SGOTableModel.get(); }
signals:
    void AddToMap(StaticGameObjectDbInfo& gameObject);
    void SGODeleted(int sgoId);
    void SGOEdited(StaticGameObjectDbInfo& gameObject);
};
