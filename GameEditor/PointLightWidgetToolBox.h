#pragma once

#include <QWidget>
#include "ui_PointLightWidgetToolBox.h"

class PointLightWidgetToolBox : public QWidget, public Ui::PointLightWidgetToolBox
{
    Q_OBJECT
protected slots:
    void on_nameFilterTxt_editingFinished();
    void on_sgoNameFilterTxt_editingFinished();
public:
signals :
    void FilterChanged();
public:
    PointLightWidgetToolBox(QWidget *parent = Q_NULLPTR);
    ~PointLightWidgetToolBox();
    QString GetNameFilter() { return this->nameFilterTxt->text().trimmed(); }
    QString GetSgoNameFilter() { return this->sgoNameFilterTxt->text().trimmed(); }
};
