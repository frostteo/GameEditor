/********************************************************************************
** Form generated from reading UI file 'SGOTableWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SGOTABLEWIDGET_H
#define UI_SGOTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SGOTableWidget
{
public:

    void setupUi(QWidget *SGOTableWidget)
    {
        if (SGOTableWidget->objectName().isEmpty())
            SGOTableWidget->setObjectName(QStringLiteral("SGOTableWidget"));
        SGOTableWidget->resize(400, 300);

        retranslateUi(SGOTableWidget);

        QMetaObject::connectSlotsByName(SGOTableWidget);
    } // setupUi

    void retranslateUi(QWidget *SGOTableWidget)
    {
        SGOTableWidget->setWindowTitle(QApplication::translate("SGOTableWidget", "SGOTableWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SGOTableWidget: public Ui_SGOTableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SGOTABLEWIDGET_H
