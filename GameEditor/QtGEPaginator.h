#pragma once

#include <QWidget>
#include "ui_QtGEPaginator.h"
#include <vector>
#include "PagingInfo.h"

class QtGEPaginator : public QWidget, public Ui::QtGEPaginator
{
    Q_OBJECT
protected slots:
    void on_firstBtn_clicked();
    void on_prevBtn_clicked();
    void on_nextBtn_clicked();
    void on_lastBtn_clicked();
    void on_pageTxt_editingFinished();
    void on_onPageList_currentIndexChanged(int index);
protected:
  void ConfigureUi();
  void UpdateData();
public slots:
  void UpdatePagingInfo(PagingInfo pagingInfo);
signals:
  void PageChanged(int pageNumber, int onPage);
public:
  QtGEPaginator(QWidget *parent = Q_NULLPTR, PagingInfo pagingInfo = PagingInfo(), std::vector<int>* onPageListValues = &(std::vector<int>{ 10, 25, 50, 100 }));
    ~QtGEPaginator();
    void SetOnPageList(std::vector<int>* onPageListValues);
    int GetPageNumber() { return this->pageTxt->text().toInt(); }
    int GetOnPageCount() { return this->onPageList->currentText().toInt(); }
};
