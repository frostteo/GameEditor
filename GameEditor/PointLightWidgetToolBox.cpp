#include "PointLightWidgetToolBox.h"

PointLightWidgetToolBox::PointLightWidgetToolBox(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
}

PointLightWidgetToolBox::~PointLightWidgetToolBox()
{
}

void PointLightWidgetToolBox::on_nameFilterTxt_editingFinished()
{
  emit FilterChanged();
}

void PointLightWidgetToolBox::on_sgoNameFilterTxt_editingFinished()
{
  emit FilterChanged();
}