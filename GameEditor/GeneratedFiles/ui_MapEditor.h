/********************************************************************************
** Form generated from reading UI file 'MapEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPEDITOR_H
#define UI_MAPEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapEditor
{
public:

    void setupUi(QWidget *MapEditor)
    {
        if (MapEditor->objectName().isEmpty())
            MapEditor->setObjectName(QStringLiteral("MapEditor"));
        MapEditor->resize(400, 300);

        retranslateUi(MapEditor);

        QMetaObject::connectSlotsByName(MapEditor);
    } // setupUi

    void retranslateUi(QWidget *MapEditor)
    {
        MapEditor->setWindowTitle(QApplication::translate("MapEditor", "MapEditor", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MapEditor: public Ui_MapEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITOR_H
