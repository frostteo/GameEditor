/********************************************************************************
** Form generated from reading UI file 'ConfigurePLRelativePosWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGUREPLRELATIVEPOSWIDGET_H
#define UI_CONFIGUREPLRELATIVEPOSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <qtdirectxwidget.h>

QT_BEGIN_NAMESPACE

class Ui_ConfigurePLRelativePosWidget
{
public:

    void setupUi(QtDirectXWidget *ConfigurePLRelativePosWidget)
    {
        if (ConfigurePLRelativePosWidget->objectName().isEmpty())
            ConfigurePLRelativePosWidget->setObjectName(QStringLiteral("ConfigurePLRelativePosWidget"));
        ConfigurePLRelativePosWidget->resize(400, 300);

        retranslateUi(ConfigurePLRelativePosWidget);

        QMetaObject::connectSlotsByName(ConfigurePLRelativePosWidget);
    } // setupUi

    void retranslateUi(QtDirectXWidget *ConfigurePLRelativePosWidget)
    {
        ConfigurePLRelativePosWidget->setWindowTitle(QApplication::translate("ConfigurePLRelativePosWidget", "ConfigurePLRelativePosWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConfigurePLRelativePosWidget: public Ui_ConfigurePLRelativePosWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREPLRELATIVEPOSWIDGET_H
