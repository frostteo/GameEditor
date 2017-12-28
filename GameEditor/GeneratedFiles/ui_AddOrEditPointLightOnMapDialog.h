/********************************************************************************
** Form generated from reading UI file 'AddOrEditPointLightOnMapDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDOREDITPOINTLIGHTONMAPDIALOG_H
#define UI_ADDOREDITPOINTLIGHTONMAPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_AddOrEditPointLightOnMapDialog
{
public:
    QGroupBox *positionGroupBox;
    QLabel *xPosLbl;
    QLabel *yPosLbl;
    QLineEdit *yPosTxt;
    QLabel *zPosLbl;
    QLineEdit *zPosTxt;
    QLineEdit *xPosTxt;
    QGroupBox *rotateGroupBox;
    QLabel *xRotateLbl;
    QLabel *yRotateLbl;
    QLineEdit *yRotateTxt;
    QLabel *zRotateLbl;
    QLineEdit *zRotateTxt;
    QLineEdit *xRotateTxt;
    QLabel *instanceNameLbl;
    QLineEdit *instanceNameTxt;
    QCheckBox *isFrozenCheckBox;
    QDialogButtonBox *buttonBox;
    QGroupBox *colorGroupBox;
    QLabel *redlbl;
    QLabel *greenLbl;
    QLabel *blueLbl;
    QLineEdit *redTxt;
    QLineEdit *greenTxt;
    QLineEdit *blueTxt;
    QGroupBox *attenuationGroupBox;
    QLabel *linearAttenuationLbl;
    QLineEdit *linearAttenuationTxt;
    QLabel *quadraticAttenuationLbl;
    QLineEdit *quadraticAttenuationTxt;

    void setupUi(QDialog *AddOrEditPointLightOnMapDialog)
    {
        if (AddOrEditPointLightOnMapDialog->objectName().isEmpty())
            AddOrEditPointLightOnMapDialog->setObjectName(QStringLiteral("AddOrEditPointLightOnMapDialog"));
        AddOrEditPointLightOnMapDialog->resize(346, 333);
        positionGroupBox = new QGroupBox(AddOrEditPointLightOnMapDialog);
        positionGroupBox->setObjectName(QStringLiteral("positionGroupBox"));
        positionGroupBox->setGeometry(QRect(20, 40, 151, 111));
        xPosLbl = new QLabel(positionGroupBox);
        xPosLbl->setObjectName(QStringLiteral("xPosLbl"));
        xPosLbl->setGeometry(QRect(10, 20, 16, 16));
        yPosLbl = new QLabel(positionGroupBox);
        yPosLbl->setObjectName(QStringLiteral("yPosLbl"));
        yPosLbl->setGeometry(QRect(10, 50, 16, 16));
        yPosTxt = new QLineEdit(positionGroupBox);
        yPosTxt->setObjectName(QStringLiteral("yPosTxt"));
        yPosTxt->setGeometry(QRect(20, 50, 113, 20));
        zPosLbl = new QLabel(positionGroupBox);
        zPosLbl->setObjectName(QStringLiteral("zPosLbl"));
        zPosLbl->setGeometry(QRect(10, 80, 16, 16));
        zPosTxt = new QLineEdit(positionGroupBox);
        zPosTxt->setObjectName(QStringLiteral("zPosTxt"));
        zPosTxt->setGeometry(QRect(20, 80, 113, 20));
        xPosTxt = new QLineEdit(positionGroupBox);
        xPosTxt->setObjectName(QStringLiteral("xPosTxt"));
        xPosTxt->setGeometry(QRect(20, 20, 113, 20));
        rotateGroupBox = new QGroupBox(AddOrEditPointLightOnMapDialog);
        rotateGroupBox->setObjectName(QStringLiteral("rotateGroupBox"));
        rotateGroupBox->setGeometry(QRect(180, 40, 151, 111));
        xRotateLbl = new QLabel(rotateGroupBox);
        xRotateLbl->setObjectName(QStringLiteral("xRotateLbl"));
        xRotateLbl->setGeometry(QRect(10, 20, 16, 16));
        yRotateLbl = new QLabel(rotateGroupBox);
        yRotateLbl->setObjectName(QStringLiteral("yRotateLbl"));
        yRotateLbl->setGeometry(QRect(10, 50, 16, 16));
        yRotateTxt = new QLineEdit(rotateGroupBox);
        yRotateTxt->setObjectName(QStringLiteral("yRotateTxt"));
        yRotateTxt->setGeometry(QRect(20, 50, 113, 20));
        zRotateLbl = new QLabel(rotateGroupBox);
        zRotateLbl->setObjectName(QStringLiteral("zRotateLbl"));
        zRotateLbl->setGeometry(QRect(10, 80, 16, 16));
        zRotateTxt = new QLineEdit(rotateGroupBox);
        zRotateTxt->setObjectName(QStringLiteral("zRotateTxt"));
        zRotateTxt->setGeometry(QRect(20, 80, 113, 20));
        xRotateTxt = new QLineEdit(rotateGroupBox);
        xRotateTxt->setObjectName(QStringLiteral("xRotateTxt"));
        xRotateTxt->setGeometry(QRect(20, 20, 113, 20));
        instanceNameLbl = new QLabel(AddOrEditPointLightOnMapDialog);
        instanceNameLbl->setObjectName(QStringLiteral("instanceNameLbl"));
        instanceNameLbl->setGeometry(QRect(20, 10, 71, 16));
        instanceNameTxt = new QLineEdit(AddOrEditPointLightOnMapDialog);
        instanceNameTxt->setObjectName(QStringLiteral("instanceNameTxt"));
        instanceNameTxt->setGeometry(QRect(90, 10, 241, 20));
        isFrozenCheckBox = new QCheckBox(AddOrEditPointLightOnMapDialog);
        isFrozenCheckBox->setObjectName(QStringLiteral("isFrozenCheckBox"));
        isFrozenCheckBox->setGeometry(QRect(260, 280, 70, 17));
        buttonBox = new QDialogButtonBox(AddOrEditPointLightOnMapDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(170, 300, 156, 23));
        buttonBox->setLayoutDirection(Qt::RightToLeft);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        colorGroupBox = new QGroupBox(AddOrEditPointLightOnMapDialog);
        colorGroupBox->setObjectName(QStringLiteral("colorGroupBox"));
        colorGroupBox->setGeometry(QRect(20, 160, 311, 51));
        redlbl = new QLabel(colorGroupBox);
        redlbl->setObjectName(QStringLiteral("redlbl"));
        redlbl->setGeometry(QRect(10, 20, 16, 16));
        greenLbl = new QLabel(colorGroupBox);
        greenLbl->setObjectName(QStringLiteral("greenLbl"));
        greenLbl->setGeometry(QRect(100, 20, 31, 16));
        blueLbl = new QLabel(colorGroupBox);
        blueLbl->setObjectName(QStringLiteral("blueLbl"));
        blueLbl->setGeometry(QRect(200, 20, 21, 16));
        redTxt = new QLineEdit(colorGroupBox);
        redTxt->setObjectName(QStringLiteral("redTxt"));
        redTxt->setGeometry(QRect(30, 20, 61, 20));
        greenTxt = new QLineEdit(colorGroupBox);
        greenTxt->setObjectName(QStringLiteral("greenTxt"));
        greenTxt->setGeometry(QRect(130, 20, 61, 20));
        blueTxt = new QLineEdit(colorGroupBox);
        blueTxt->setObjectName(QStringLiteral("blueTxt"));
        blueTxt->setGeometry(QRect(220, 20, 61, 20));
        attenuationGroupBox = new QGroupBox(AddOrEditPointLightOnMapDialog);
        attenuationGroupBox->setObjectName(QStringLiteral("attenuationGroupBox"));
        attenuationGroupBox->setGeometry(QRect(20, 220, 311, 51));
        linearAttenuationLbl = new QLabel(attenuationGroupBox);
        linearAttenuationLbl->setObjectName(QStringLiteral("linearAttenuationLbl"));
        linearAttenuationLbl->setGeometry(QRect(10, 20, 31, 16));
        linearAttenuationTxt = new QLineEdit(attenuationGroupBox);
        linearAttenuationTxt->setObjectName(QStringLiteral("linearAttenuationTxt"));
        linearAttenuationTxt->setGeometry(QRect(40, 20, 91, 20));
        quadraticAttenuationLbl = new QLabel(attenuationGroupBox);
        quadraticAttenuationLbl->setObjectName(QStringLiteral("quadraticAttenuationLbl"));
        quadraticAttenuationLbl->setGeometry(QRect(140, 20, 47, 13));
        quadraticAttenuationTxt = new QLineEdit(attenuationGroupBox);
        quadraticAttenuationTxt->setObjectName(QStringLiteral("quadraticAttenuationTxt"));
        quadraticAttenuationTxt->setGeometry(QRect(190, 20, 91, 20));
        QWidget::setTabOrder(instanceNameTxt, xPosTxt);
        QWidget::setTabOrder(xPosTxt, yPosTxt);
        QWidget::setTabOrder(yPosTxt, zPosTxt);
        QWidget::setTabOrder(zPosTxt, xRotateTxt);
        QWidget::setTabOrder(xRotateTxt, yRotateTxt);
        QWidget::setTabOrder(yRotateTxt, zRotateTxt);
        QWidget::setTabOrder(zRotateTxt, redTxt);
        QWidget::setTabOrder(redTxt, greenTxt);
        QWidget::setTabOrder(greenTxt, blueTxt);
        QWidget::setTabOrder(blueTxt, linearAttenuationTxt);
        QWidget::setTabOrder(linearAttenuationTxt, quadraticAttenuationTxt);
        QWidget::setTabOrder(quadraticAttenuationTxt, isFrozenCheckBox);

        retranslateUi(AddOrEditPointLightOnMapDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddOrEditPointLightOnMapDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddOrEditPointLightOnMapDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddOrEditPointLightOnMapDialog);
    } // setupUi

    void retranslateUi(QDialog *AddOrEditPointLightOnMapDialog)
    {
        AddOrEditPointLightOnMapDialog->setWindowTitle(QApplication::translate("AddOrEditPointLightOnMapDialog", "add/edit point light on map instance", Q_NULLPTR));
        positionGroupBox->setTitle(QApplication::translate("AddOrEditPointLightOnMapDialog", "Position", Q_NULLPTR));
        xPosLbl->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "x", Q_NULLPTR));
        yPosLbl->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "y", Q_NULLPTR));
        zPosLbl->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "z", Q_NULLPTR));
        rotateGroupBox->setTitle(QApplication::translate("AddOrEditPointLightOnMapDialog", "Rotate", Q_NULLPTR));
        xRotateLbl->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "x", Q_NULLPTR));
        yRotateLbl->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "y", Q_NULLPTR));
        zRotateLbl->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "z", Q_NULLPTR));
        instanceNameLbl->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "instance name", Q_NULLPTR));
        isFrozenCheckBox->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "Is frozen", Q_NULLPTR));
        colorGroupBox->setTitle(QApplication::translate("AddOrEditPointLightOnMapDialog", "Color", Q_NULLPTR));
        redlbl->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "red", Q_NULLPTR));
        greenLbl->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "green", Q_NULLPTR));
        blueLbl->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "blue", Q_NULLPTR));
        attenuationGroupBox->setTitle(QApplication::translate("AddOrEditPointLightOnMapDialog", "attenuation", Q_NULLPTR));
        linearAttenuationLbl->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "linear", Q_NULLPTR));
        quadraticAttenuationLbl->setText(QApplication::translate("AddOrEditPointLightOnMapDialog", "quadratic", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddOrEditPointLightOnMapDialog: public Ui_AddOrEditPointLightOnMapDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDOREDITPOINTLIGHTONMAPDIALOG_H
