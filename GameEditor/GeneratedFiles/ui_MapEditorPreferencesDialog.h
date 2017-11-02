/********************************************************************************
** Form generated from reading UI file 'MapEditorPreferencesDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPEDITORPREFERENCESDIALOG_H
#define UI_MAPEDITORPREFERENCESDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapEditorPreferencesDialog
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *objectRotationLbl;
    QLineEdit *objectRotationTxt;
    QLabel *objectMoveLbl;
    QLineEdit *objectMoveTxt;
    QLabel *cameraRotationLbl;
    QLineEdit *cameraRotationTxt;
    QLabel *cameraZoomLbl;
    QLineEdit *cameraZoomTxt;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *MapEditorPreferencesDialog)
    {
        if (MapEditorPreferencesDialog->objectName().isEmpty())
            MapEditorPreferencesDialog->setObjectName(QStringLiteral("MapEditorPreferencesDialog"));
        MapEditorPreferencesDialog->resize(198, 180);
        MapEditorPreferencesDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        groupBox = new QGroupBox(MapEditorPreferencesDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 181, 131));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        objectRotationLbl = new QLabel(groupBox);
        objectRotationLbl->setObjectName(QStringLiteral("objectRotationLbl"));

        gridLayout->addWidget(objectRotationLbl, 0, 0, 1, 1);

        objectRotationTxt = new QLineEdit(groupBox);
        objectRotationTxt->setObjectName(QStringLiteral("objectRotationTxt"));
        objectRotationTxt->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(objectRotationTxt, 0, 1, 1, 1);

        objectMoveLbl = new QLabel(groupBox);
        objectMoveLbl->setObjectName(QStringLiteral("objectMoveLbl"));

        gridLayout->addWidget(objectMoveLbl, 1, 0, 1, 1);

        objectMoveTxt = new QLineEdit(groupBox);
        objectMoveTxt->setObjectName(QStringLiteral("objectMoveTxt"));
        objectMoveTxt->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(objectMoveTxt, 1, 1, 1, 1);

        cameraRotationLbl = new QLabel(groupBox);
        cameraRotationLbl->setObjectName(QStringLiteral("cameraRotationLbl"));

        gridLayout->addWidget(cameraRotationLbl, 2, 0, 1, 1);

        cameraRotationTxt = new QLineEdit(groupBox);
        cameraRotationTxt->setObjectName(QStringLiteral("cameraRotationTxt"));
        cameraRotationTxt->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(cameraRotationTxt, 2, 1, 1, 1);

        cameraZoomLbl = new QLabel(groupBox);
        cameraZoomLbl->setObjectName(QStringLiteral("cameraZoomLbl"));

        gridLayout->addWidget(cameraZoomLbl, 3, 0, 1, 1);

        cameraZoomTxt = new QLineEdit(groupBox);
        cameraZoomTxt->setObjectName(QStringLiteral("cameraZoomTxt"));
        cameraZoomTxt->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(cameraZoomTxt, 3, 1, 1, 1);

        buttonBox = new QDialogButtonBox(MapEditorPreferencesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 150, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(MapEditorPreferencesDialog);

        QMetaObject::connectSlotsByName(MapEditorPreferencesDialog);
    } // setupUi

    void retranslateUi(QWidget *MapEditorPreferencesDialog)
    {
        MapEditorPreferencesDialog->setWindowTitle(QApplication::translate("MapEditorPreferencesDialog", "Map editor preferences", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MapEditorPreferencesDialog", "Movement speeds", Q_NULLPTR));
        objectRotationLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "Object rotation", Q_NULLPTR));
        objectMoveLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "Object move", Q_NULLPTR));
        cameraRotationLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "Camera rotation", Q_NULLPTR));
        cameraZoomLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "Camera zoom", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MapEditorPreferencesDialog: public Ui_MapEditorPreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITORPREFERENCESDIALOG_H
