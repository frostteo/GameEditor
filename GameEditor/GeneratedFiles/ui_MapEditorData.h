/********************************************************************************
** Form generated from reading UI file 'MapEditorData.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPEDITORDATA_H
#define UI_MAPEDITORDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapEditorData
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;

    void setupUi(QWidget *MapEditorData)
    {
        if (MapEditorData->objectName().isEmpty())
            MapEditorData->setObjectName(QStringLiteral("MapEditorData"));
        MapEditorData->resize(469, 336);
        gridLayout = new QGridLayout(MapEditorData);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(MapEditorData);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(MapEditorData);

        QMetaObject::connectSlotsByName(MapEditorData);
    } // setupUi

    void retranslateUi(QWidget *MapEditorData)
    {
        MapEditorData->setWindowTitle(QApplication::translate("MapEditorData", "map objects", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MapEditorData: public Ui_MapEditorData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITORDATA_H
