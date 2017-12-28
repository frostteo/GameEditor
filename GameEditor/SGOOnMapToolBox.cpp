#include "SGOOnMapToolBox.h"

SGOOnMapToolBox::SGOOnMapToolBox(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
}

SGOOnMapToolBox::~SGOOnMapToolBox()
{
}

void SGOOnMapToolBox::on_SGONameFilterTxt_editingFinished()
{
  emit FilterChanged();
}

void SGOOnMapToolBox::on_instanceNameFilterTxt_editingFinished()
{
  emit FilterChanged();
}

void SGOOnMapToolBox::on_gameObjectTypeFilter_currentIndexChanged(int index)
{
  emit FilterChanged();
}