#include "SGOWidgetToolBox.h"

SGOWidgetToolBox::SGOWidgetToolBox(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

SGOWidgetToolBox::~SGOWidgetToolBox()
{
}

void SGOWidgetToolBox::on_SGONameFilterTxt_editingFinished()
{
  emit FilterChanged();
}

void SGOWidgetToolBox::on_SGOModelFilterTxt_editingFinished()
{
  emit FilterChanged();
}