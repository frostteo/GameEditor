/********************************************************************************
** Form generated from reading UI file 'PreviewStaticGOWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEWSTATICGOWIDGET_H
#define UI_PREVIEWSTATICGOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreviewStaticGOWidget
{
public:

    void setupUi(QWidget *PreviewStaticGOWidget)
    {
        if (PreviewStaticGOWidget->objectName().isEmpty())
            PreviewStaticGOWidget->setObjectName(QStringLiteral("PreviewStaticGOWidget"));
        PreviewStaticGOWidget->resize(400, 300);

        retranslateUi(PreviewStaticGOWidget);

        QMetaObject::connectSlotsByName(PreviewStaticGOWidget);
    } // setupUi

    void retranslateUi(QWidget *PreviewStaticGOWidget)
    {
        PreviewStaticGOWidget->setWindowTitle(QApplication::translate("PreviewStaticGOWidget", "Preview", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PreviewStaticGOWidget: public Ui_PreviewStaticGOWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEWSTATICGOWIDGET_H
