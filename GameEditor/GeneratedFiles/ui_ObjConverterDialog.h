/********************************************************************************
** Form generated from reading UI file 'ObjConverterDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJCONVERTERDIALOG_H
#define UI_OBJCONVERTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjConverterDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *errorsMsg;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *objFileNameTxt;
    QPushButton *selectObjFileBtn;
    QLabel *meshFileNameLbl;
    QLineEdit *meshFileNameTxt;
    QCheckBox *needReplaceMaterialIfExistsFlag;
    QLabel *objFileNameLbl;
    QLabel *materialLibraryInfo;

    void setupUi(QDialog *ObjConverterDialog)
    {
        if (ObjConverterDialog->objectName().isEmpty())
            ObjConverterDialog->setObjectName(QStringLiteral("ObjConverterDialog"));
        ObjConverterDialog->resize(404, 191);
        ObjConverterDialog->setLayoutDirection(Qt::LeftToRight);
        buttonBox = new QDialogButtonBox(ObjConverterDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(240, 160, 156, 23));
        buttonBox->setLayoutDirection(Qt::RightToLeft);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        errorsMsg = new QLabel(ObjConverterDialog);
        errorsMsg->setObjectName(QStringLiteral("errorsMsg"));
        errorsMsg->setGeometry(QRect(10, 110, 381, 51));
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
        layoutWidget = new QWidget(ObjConverterDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 388, 93));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        objFileNameTxt = new QLineEdit(layoutWidget);
        objFileNameTxt->setObjectName(QStringLiteral("objFileNameTxt"));
        objFileNameTxt->setReadOnly(true);

        gridLayout->addWidget(objFileNameTxt, 0, 1, 1, 2);

        selectObjFileBtn = new QPushButton(layoutWidget);
        selectObjFileBtn->setObjectName(QStringLiteral("selectObjFileBtn"));

        gridLayout->addWidget(selectObjFileBtn, 0, 3, 1, 1);

        meshFileNameLbl = new QLabel(layoutWidget);
        meshFileNameLbl->setObjectName(QStringLiteral("meshFileNameLbl"));

        gridLayout->addWidget(meshFileNameLbl, 1, 0, 1, 2);

        meshFileNameTxt = new QLineEdit(layoutWidget);
        meshFileNameTxt->setObjectName(QStringLiteral("meshFileNameTxt"));
        meshFileNameTxt->setMaxLength(255);

        gridLayout->addWidget(meshFileNameTxt, 1, 2, 1, 2);

        needReplaceMaterialIfExistsFlag = new QCheckBox(layoutWidget);
        needReplaceMaterialIfExistsFlag->setObjectName(QStringLiteral("needReplaceMaterialIfExistsFlag"));

        gridLayout->addWidget(needReplaceMaterialIfExistsFlag, 3, 0, 1, 1);

        objFileNameLbl = new QLabel(layoutWidget);
        objFileNameLbl->setObjectName(QStringLiteral("objFileNameLbl"));

        gridLayout->addWidget(objFileNameLbl, 0, 0, 1, 1);

        materialLibraryInfo = new QLabel(layoutWidget);
        materialLibraryInfo->setObjectName(QStringLiteral("materialLibraryInfo"));
        QPalette palette1;
        QBrush brush3(QColor(0, 0, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        materialLibraryInfo->setPalette(palette1);

        gridLayout->addWidget(materialLibraryInfo, 2, 0, 1, 4);


        retranslateUi(ObjConverterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ObjConverterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ObjConverterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ObjConverterDialog);
    } // setupUi

    void retranslateUi(QDialog *ObjConverterDialog)
    {
        ObjConverterDialog->setWindowTitle(QApplication::translate("ObjConverterDialog", "Convert .obj to game editor model format", Q_NULLPTR));
        errorsMsg->setText(QString());
        selectObjFileBtn->setText(QApplication::translate("ObjConverterDialog", "Select", Q_NULLPTR));
        meshFileNameLbl->setText(QApplication::translate("ObjConverterDialog", "Game editor model file name", Q_NULLPTR));
        needReplaceMaterialIfExistsFlag->setText(QApplication::translate("ObjConverterDialog", "need replace material if exists", Q_NULLPTR));
        objFileNameLbl->setText(QApplication::translate("ObjConverterDialog", ".Obj file name", Q_NULLPTR));
        materialLibraryInfo->setText(QApplication::translate("ObjConverterDialog", ".mtl material library with same name as object file must be in directory", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ObjConverterDialog: public Ui_ObjConverterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJCONVERTERDIALOG_H
