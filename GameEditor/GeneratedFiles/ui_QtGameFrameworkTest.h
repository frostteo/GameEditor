/********************************************************************************
** Form generated from reading UI file 'QtGameFrameworkTest.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGAMEFRAMEWORKTEST_H
#define UI_QTGAMEFRAMEWORKTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGameFrameworkTest
{
public:

    void setupUi(QWidget *QtGameFrameworkTest)
    {
        if (QtGameFrameworkTest->objectName().isEmpty())
            QtGameFrameworkTest->setObjectName(QStringLiteral("QtGameFrameworkTest"));
        QtGameFrameworkTest->resize(400, 300);

        retranslateUi(QtGameFrameworkTest);

        QMetaObject::connectSlotsByName(QtGameFrameworkTest);
    } // setupUi

    void retranslateUi(QWidget *QtGameFrameworkTest)
    {
        QtGameFrameworkTest->setWindowTitle(QApplication::translate("QtGameFrameworkTest", "QtGameFrameworkTest", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGameFrameworkTest: public Ui_QtGameFrameworkTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGAMEFRAMEWORKTEST_H
