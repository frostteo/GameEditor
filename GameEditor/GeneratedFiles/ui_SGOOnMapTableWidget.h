/********************************************************************************
** Form generated from reading UI file 'SGOOnMapTableWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SGOONMAPTABLEWIDGET_H
#define UI_SGOONMAPTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SGOOnMapTableWidget
{
public:

    void setupUi(QWidget *SGOOnMapTableWidget)
    {
        if (SGOOnMapTableWidget->objectName().isEmpty())
            SGOOnMapTableWidget->setObjectName(QStringLiteral("SGOOnMapTableWidget"));
        SGOOnMapTableWidget->resize(400, 300);

        retranslateUi(SGOOnMapTableWidget);

        QMetaObject::connectSlotsByName(SGOOnMapTableWidget);
    } // setupUi

    void retranslateUi(QWidget *SGOOnMapTableWidget)
    {
        SGOOnMapTableWidget->setWindowTitle(QApplication::translate("SGOOnMapTableWidget", "SGOOnMapTableWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SGOOnMapTableWidget: public Ui_SGOOnMapTableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SGOONMAPTABLEWIDGET_H
