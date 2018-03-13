#pragma once

#include <memory>
#include <QDialog>
#include "ui_MapEditorPreferencesDialog.h"
#include "MapEditorPreferences.h"

class MapEditorPreferencesDialog : public QDialog, public Ui::MapEditorPreferencesDialog
{
  Q_OBJECT
private:
    MapEditorPreferences* m_mapEditorPreferences;
public:
    MapEditorPreferencesDialog(QWidget *parent = Q_NULLPTR);
    ~MapEditorPreferencesDialog();
    void SetMapEditorPreferences(MapEditorPreferences* mapEditorPreferences);
    void done(int result) override;
};
