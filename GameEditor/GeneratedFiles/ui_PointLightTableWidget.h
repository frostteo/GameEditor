/********************************************************************************
** Form generated from reading UI file 'PointLightTableWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POINTLIGHTTABLEWIDGET_H
#define UI_POINTLIGHTTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PointLightTableWidget
{
public:

    void setupUi(QWidget *PointLightTableWidget)
    {
        if (PointLightTableWidget->objectName().isEmpty())
            PointLightTableWidget->setObjectName(QStringLiteral("PointLightTableWidget"));
        PointLightTableWidget->resize(400, 300);

        retranslateUi(PointLightTableWidget);

        QMetaObject::connectSlotsByName(PointLightTableWidget);
    } // setupUi

    void retranslateUi(QWidget *PointLightTableWidget)
    {
        PointLightTableWidget->setWindowTitle(QApplication::translate("PointLightTableWidget", "PointLightTableWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PointLightTableWidget: public Ui_PointLightTableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINTLIGHTTABLEWIDGET_H
