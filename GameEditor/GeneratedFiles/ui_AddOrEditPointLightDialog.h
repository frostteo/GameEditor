/********************************************************************************
** Form generated from reading UI file 'AddOrEditPointLightDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDOREDITPOINTLIGHTDIALOG_H
#define UI_ADDOREDITPOINTLIGHTDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddOrEditPointLightDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *errorsMsgLbl;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *nameLbl;
    QLineEdit *nameTxt;
    QLabel *sgoNameLbl;
    QLineEdit *sgoNameTxt;
    QLabel *relPosXLbl;
    QLineEdit *relPosXTxt;
    QLabel *relPosYLbl;
    QLineEdit *relPosYTxt;
    QLabel *relPosZLbl;
    QLineEdit *relPosZTxt;
    QLabel *linearAttenuationLbl;
    QLineEdit *linearAttenuationTxt;
    QLabel *quadraticAttenuationLbl;
    QLineEdit *quadraticAttenuationTxt;

    void setupUi(QDialog *AddOrEditPointLightDialog)
    {
        if (AddOrEditPointLightDialog->objectName().isEmpty())
            AddOrEditPointLightDialog->setObjectName(QStringLiteral("AddOrEditPointLightDialog"));
        AddOrEditPointLightDialog->resize(288, 270);
        AddOrEditPointLightDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox = new QDialogButtonBox(AddOrEditPointLightDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(120, 240, 156, 23));
        buttonBox->setLayoutDirection(Qt::RightToLeft);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        errorsMsgLbl = new QLabel(AddOrEditPointLightDialog);
        errorsMsgLbl->setObjectName(QStringLiteral("errorsMsgLbl"));
        errorsMsgLbl->setGeometry(QRect(20, 190, 261, 51));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        errorsMsgLbl->setPalette(palette);
        errorsMsgLbl->setWordWrap(true);
        layoutWidget = new QWidget(AddOrEditPointLightDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 259, 178));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        nameLbl = new QLabel(layoutWidget);
        nameLbl->setObjectName(QStringLiteral("nameLbl"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLbl);

        nameTxt = new QLineEdit(layoutWidget);
        nameTxt->setObjectName(QStringLiteral("nameTxt"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameTxt);

        sgoNameLbl = new QLabel(layoutWidget);
        sgoNameLbl->setObjectName(QStringLiteral("sgoNameLbl"));
        sgoNameLbl->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(1, QFormLayout::LabelRole, sgoNameLbl);

        sgoNameTxt = new QLineEdit(layoutWidget);
        sgoNameTxt->setObjectName(QStringLiteral("sgoNameTxt"));

        formLayout->setWidget(1, QFormLayout::FieldRole, sgoNameTxt);

        relPosXLbl = new QLabel(layoutWidget);
        relPosXLbl->setObjectName(QStringLiteral("relPosXLbl"));

        formLayout->setWidget(2, QFormLayout::LabelRole, relPosXLbl);

        relPosXTxt = new QLineEdit(layoutWidget);
        relPosXTxt->setObjectName(QStringLiteral("relPosXTxt"));

        formLayout->setWidget(2, QFormLayout::FieldRole, relPosXTxt);

        relPosYLbl = new QLabel(layoutWidget);
        relPosYLbl->setObjectName(QStringLiteral("relPosYLbl"));

        formLayout->setWidget(3, QFormLayout::LabelRole, relPosYLbl);

        relPosYTxt = new QLineEdit(layoutWidget);
        relPosYTxt->setObjectName(QStringLiteral("relPosYTxt"));

        formLayout->setWidget(3, QFormLayout::FieldRole, relPosYTxt);

        relPosZLbl = new QLabel(layoutWidget);
        relPosZLbl->setObjectName(QStringLiteral("relPosZLbl"));

        formLayout->setWidget(4, QFormLayout::LabelRole, relPosZLbl);

        relPosZTxt = new QLineEdit(layoutWidget);
        relPosZTxt->setObjectName(QStringLiteral("relPosZTxt"));

        formLayout->setWidget(4, QFormLayout::FieldRole, relPosZTxt);

        linearAttenuationLbl = new QLabel(layoutWidget);
        linearAttenuationLbl->setObjectName(QStringLiteral("linearAttenuationLbl"));

        formLayout->setWidget(5, QFormLayout::LabelRole, linearAttenuationLbl);

        linearAttenuationTxt = new QLineEdit(layoutWidget);
        linearAttenuationTxt->setObjectName(QStringLiteral("linearAttenuationTxt"));

        formLayout->setWidget(5, QFormLayout::FieldRole, linearAttenuationTxt);

        quadraticAttenuationLbl = new QLabel(layoutWidget);
        quadraticAttenuationLbl->setObjectName(QStringLiteral("quadraticAttenuationLbl"));

        formLayout->setWidget(6, QFormLayout::LabelRole, quadraticAttenuationLbl);

        quadraticAttenuationTxt = new QLineEdit(layoutWidget);
        quadraticAttenuationTxt->setObjectName(QStringLiteral("quadraticAttenuationTxt"));

        formLayout->setWidget(6, QFormLayout::FieldRole, quadraticAttenuationTxt);


        retranslateUi(AddOrEditPointLightDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddOrEditPointLightDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddOrEditPointLightDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddOrEditPointLightDialog);
    } // setupUi

    void retranslateUi(QDialog *AddOrEditPointLightDialog)
    {
        AddOrEditPointLightDialog->setWindowTitle(QApplication::translate("AddOrEditPointLightDialog", "Add or edit point light", Q_NULLPTR));
        errorsMsgLbl->setText(QString());
        nameLbl->setText(QApplication::translate("AddOrEditPointLightDialog", "Name", Q_NULLPTR));
        sgoNameLbl->setText(QApplication::translate("AddOrEditPointLightDialog", "Static game object name", Q_NULLPTR));
        relPosXLbl->setText(QApplication::translate("AddOrEditPointLightDialog", "Relative position X", Q_NULLPTR));
        relPosYLbl->setText(QApplication::translate("AddOrEditPointLightDialog", "Relative position Y", Q_NULLPTR));
        relPosZLbl->setText(QApplication::translate("AddOrEditPointLightDialog", "Relative position Z", Q_NULLPTR));
        linearAttenuationLbl->setText(QApplication::translate("AddOrEditPointLightDialog", "Linear attenuation", Q_NULLPTR));
        quadraticAttenuationLbl->setText(QApplication::translate("AddOrEditPointLightDialog", "Quadratic attenuation", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddOrEditPointLightDialog: public Ui_AddOrEditPointLightDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDOREDITPOINTLIGHTDIALOG_H
