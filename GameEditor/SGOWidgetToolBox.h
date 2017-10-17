#pragma once

#include <QWidget>
#include "ui_SGOWidgetToolBox.h"

class SGOWidgetToolBox : public QWidget
{
    Q_OBJECT
protected slots:
    void on_SGONameFilterTxt_editingFinished();
    void on_SGOModelFilterTxt_editingFinished();
public:
signals :
  void FilterChanged();
public:
    SGOWidgetToolBox(QWidget *parent = Q_NULLPTR);
    ~SGOWidgetToolBox();
    QString GetSGONameFilter() { return this->ui.SGONameFilterTxt->text().trimmed(); }
    QString GetSGOModelFilter() { return this->ui.SGOModelFilterTxt->text().trimmed(); }
    Ui::SGOWidgetToolBox ui;
};
