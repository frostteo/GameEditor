#include "QtGEPaginator.h"

QtGEPaginator::QtGEPaginator(QWidget *parent, PagingInfo pagingInfo, std::vector<int>* onPageListValues)
    : QWidget(parent)
{
    setupUi(this);
    ConfigureUi();

    UpdatePagingInfo(pagingInfo);
    SetOnPageList(onPageListValues);
}

void QtGEPaginator::SetOnPageList(std::vector<int>* onPageListValues)
{
  this->onPageList->clear();
  for (auto& onPageCount : (*onPageListValues))
    this->onPageList->addItem(QString::number(onPageCount));
}

void QtGEPaginator::ConfigureUi()
{
  this->firstBtn->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
  this->prevBtn->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
  this->nextBtn->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
  this->lastBtn->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
}

QtGEPaginator::~QtGEPaginator()
{
}

void QtGEPaginator::on_firstBtn_clicked()
{
  this->pageTxt->setText("1");
  UpdateData();
}

void QtGEPaginator::on_prevBtn_clicked()
{
  int currentPage = GetPageNumber();
  if (currentPage > 1) --currentPage;
  this->pageTxt->setText(QString::number(currentPage));

  UpdateData();
}

void QtGEPaginator::on_nextBtn_clicked()
{
  int currentPage = GetPageNumber();
  int pageCount = this->countTxt->text().toInt();
  if (currentPage < pageCount) ++currentPage;
  this->pageTxt->setText(QString::number(currentPage));

  UpdateData();
}

void QtGEPaginator::on_lastBtn_clicked()
{
  this->pageTxt->setText(this->countTxt->text());
  UpdateData();
}

void QtGEPaginator::on_pageTxt_editingFinished()
{
  UpdateData();
}

void QtGEPaginator::on_onPageList_currentIndexChanged(int index)
{
  UpdateData();
}

void QtGEPaginator::UpdateData()
{
  int pageNumber = GetPageNumber();
  int onPage = GetOnPageCount();
  emit PageChanged(pageNumber, onPage);
}

void QtGEPaginator::UpdatePagingInfo(PagingInfo pagingInfo)
{
  this->pageTxt->setValidator(new QIntValidator(1, pagingInfo.pageCount, this));
  this->pageTxt->setText(QString::number(pagingInfo.pageNumber));
  this->countTxt->setText(QString::number(pagingInfo.pageCount));

  this->firstBtn->setEnabled(pagingInfo.pageNumber > 1);
  this->prevBtn->setEnabled(pagingInfo.pageNumber > 1);

  this->lastBtn->setEnabled(pagingInfo.pageNumber < pagingInfo.pageCount);
  this->nextBtn->setEnabled(pagingInfo.pageNumber < pagingInfo.pageCount);
}