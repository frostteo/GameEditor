#pragma once

#include <memory>
#include <QWidget>
#include <qboxlayout.h>
#include "ui_SGOTableWidget.h"
#include "qtableview.h"
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
  void UpdateTable();
  void on_previewSGOBtn_clicked();
protected:
  void configureTable();
  void configureUI();
  void configurePaginator();
public:
    SGOTableWidget(QString& pathToModels, QString& pathToMaterials, QWidget *parent = Q_NULLPTR);
    ~SGOTableWidget();
    void SetPathToModels(QString& path) { m_pathToModels = path; }
    void SetPathToMaterials(QString& path) { m_pathToMaterials = path; }
};
