/********************************************************************************
** Form generated from reading UI file 'QtDirectXWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDIRECTXWIDGET_H
#define UI_QTDIRECTXWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtDirectXWidget
{
public:

    void setupUi(QWidget *QtDirectXWidget)
    {
        if (QtDirectXWidget->objectName().isEmpty())
            QtDirectXWidget->setObjectName(QStringLiteral("QtDirectXWidget"));
        QtDirectXWidget->resize(400, 300);

        retranslateUi(QtDirectXWidget);

        QMetaObject::connectSlotsByName(QtDirectXWidget);
    } // setupUi

    void retranslateUi(QWidget *QtDirectXWidget)
    {
        QtDirectXWidget->setWindowTitle(QApplication::translate("QtDirectXWidget", "QtDirectXWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtDirectXWidget: public Ui_QtDirectXWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDIRECTXWIDGET_H
