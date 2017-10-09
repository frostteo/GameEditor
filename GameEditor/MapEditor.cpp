#include "MapEditor.h"

MapEditor::MapEditor(QString pathToModels, QString pathToMaterials, QWidget *parent)
  : QtDirectXWidget(pathToModels, pathToMaterials, parent)
{

}

MapEditor::~MapEditor()
{
}
