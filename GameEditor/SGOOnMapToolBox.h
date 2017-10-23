#pragma once

#include <QWidget>
#include "ui_SGOOnMapToolBox.h"

class SGOOnMapToolBox : public QWidget, public Ui::SGOOnMapToolBox
{
    Q_OBJECT
protected slots:
    void on_SGONameFilterTxt_editingFinished();
    void on_instanceNameFilterTxt_editingFinished();
public:
signals :
  void FilterChanged();
public:
    SGOOnMapToolBox(QWidget *parent = Q_NULLPTR);
    ~SGOOnMapToolBox();
    QString GetSGONameFilter() { return this->SGONameFilterTxt->text().trimmed(); }
    QString GetInstanceNameFilter() { return this->instanceNameFilterTxt->text().trimmed(); }
};
