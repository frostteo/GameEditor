/********************************************************************************
** Form generated from reading UI file 'AddStaticGameObjectDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSTATICGAMEOBJECTDIALOG_H
#define UI_ADDSTATICGAMEOBJECTDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddStaticGameObjectDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *errorsMsg;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *staticGONameEdit;
    QLabel *label_2;
    QLineEdit *staticGOModelEdit;
    QPushButton *chooseModelFileBtn;

    void setupUi(QDialog *AddStaticGameObjectDialog)
    {
        if (AddStaticGameObjectDialog->objectName().isEmpty())
            AddStaticGameObjectDialog->setObjectName(QStringLiteral("AddStaticGameObjectDialog"));
        AddStaticGameObjectDialog->resize(386, 171);
        buttonBox = new QDialogButtonBox(AddStaticGameObjectDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(220, 140, 156, 23));
        buttonBox->setLayoutDirection(Qt::RightToLeft);
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);
        errorsMsg = new QLabel(AddStaticGameObjectDialog);
        errorsMsg->setObjectName(QStringLiteral("errorsMsg"));
        errorsMsg->setGeometry(QRect(10, 90, 261, 51));
        QPalette palette;
        QBrush brush(QColor(255, 7, 19, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(254, 3, 7, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        errorsMsg->setPalette(palette);
        layoutWidget = new QWidget(AddStaticGameObjectDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 371, 61));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        staticGONameEdit = new QLineEdit(layoutWidget);
        staticGONameEdit->setObjectName(QStringLiteral("staticGONameEdit"));
        staticGONameEdit->setMaxLength(256);

        gridLayout->addWidget(staticGONameEdit, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        staticGOModelEdit = new QLineEdit(layoutWidget);
        staticGOModelEdit->setObjectName(QStringLiteral("staticGOModelEdit"));
        staticGOModelEdit->setEnabled(true);
        staticGOModelEdit->setMaxLength(256);
        staticGOModelEdit->setReadOnly(true);

        gridLayout->addWidget(staticGOModelEdit, 1, 1, 1, 1);

        chooseModelFileBtn = new QPushButton(layoutWidget);
        chooseModelFileBtn->setObjectName(QStringLiteral("chooseModelFileBtn"));

        gridLayout->addWidget(chooseModelFileBtn, 1, 2, 1, 1);


        retranslateUi(AddStaticGameObjectDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddStaticGameObjectDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddStaticGameObjectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddStaticGameObjectDialog);
    } // setupUi

    void retranslateUi(QDialog *AddStaticGameObjectDialog)
    {
        AddStaticGameObjectDialog->setWindowTitle(QApplication::translate("AddStaticGameObjectDialog", "Add/Edit static game object", Q_NULLPTR));
        errorsMsg->setText(QString());
        label->setText(QApplication::translate("AddStaticGameObjectDialog", "Name", Q_NULLPTR));
        label_2->setText(QApplication::translate("AddStaticGameObjectDialog", "Model file name", Q_NULLPTR));
        chooseModelFileBtn->setText(QApplication::translate("AddStaticGameObjectDialog", "select", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddStaticGameObjectDialog: public Ui_AddStaticGameObjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSTATICGAMEOBJECTDIALOG_H
