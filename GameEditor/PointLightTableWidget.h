#pragma once

#include <QWidget>
#include "ui_PointLightTableWidget.h"
#include <memory>
#include <algorithm>
#include <qtableview.h>
#include <qboxlayout.h>
#include "PointLightWidgetToolBox.h"
#include "PointLightTM.h"
#include "QtGEPaginator.h"
#include "AddOrEditPointLightDialog.h"

class PointLightTableWidget : public QWidget, public Ui::PointLightTableWidget
{
    Q_OBJECT
private:
  std::unique_ptr<PointLightWidgetToolBox> m_toolBox;
  std::unique_ptr<QTableView> m_table;
  std::unique_ptr<PointLightTM> m_tableModel;
  std::unique_ptr<QtGEPaginator> m_paginator;

protected slots:
  void on_addPointLightBtn_clicked();
  void on_editPointLightBtn_clicked();
  void on_deletePointLightBtn_clicked();

  void editBtnsStateConfigure();
  void RowSelected(const QItemSelection& selected, const QItemSelection& deselected);
  void PaginatorPageChanged(int pageNumber, int onPage);
  void HeaderSectionClicked(int sectionIndex);
protected:
  void configureTable();
  void configureUI();
  void configurePaginator();
public slots:
  void UpdateTable();
public:
    PointLightTableWidget(QWidget *parent = Q_NULLPTR);
    ~PointLightTableWidget();
};
