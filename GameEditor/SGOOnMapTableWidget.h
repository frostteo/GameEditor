#pragma once

#include <QWidget>
#include <qtableview.h>
#include <qboxlayout.h>
#include <memory>
#include "ui_SGOOnMapTableWidget.h"
#include "QtGEPaginator.h"
#include "SGOOnMapTM.h"
#include "SGOOnMapToolBox.h"
#include "MapEditorControl.h"

class SGOOnMapTableWidget : public QWidget, public Ui::SGOOnMapTableWidget
{
    Q_OBJECT
private:
  std::unique_ptr<SGOOnMapToolBox> m_toolBox;
  std::unique_ptr<QTableView> m_table;
  SGOOnMapTM* m_tableModel;
  std::unique_ptr<QtGEPaginator> m_paginator;

  std::shared_ptr<MapEditorControl> m_mapEditorControl;
protected slots:
  void editBtnsStateConfigure();
  void TableRowSelected(const QItemSelection& selected, const QItemSelection& deselected);
  void PaginatorPageChanged(int pageNumber, int onPage);
  void HeaderSectionClicked(int sectionIndex);
  void UpdateTable();
  
  void DeleteBtnClicked();
  void EditBtnClicked();
  void CloneBtnClicked();
  void FreezeAllBtnClicked();
  void UnfreezeAllBtnClicked();

  void ClearSelection() { m_table->selectionModel()->clearSelection(); }
protected:
  void configureTable();
  void configureUI();
  void configurePaginator();
  void configureToolBox();
  std::vector<int> GetSelectedIds();
public:
  SGOOnMapTableWidget(std::shared_ptr<MapEditorControl> mapEditorControl, QWidget *parent = Q_NULLPTR);
  ~SGOOnMapTableWidget();
};
