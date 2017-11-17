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
#include <QtWidgets/QCheckBox>
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
    QGroupBox *movementSpeedsGroup;
    QGridLayout *gridLayout;
    QLabel *objectRotationLbl;
    QLineEdit *objectRotationTxt;
    QLabel *objectMoveLbl;
    QLineEdit *objectMoveTxt;
    QLabel *cameraRotationLbl;
    QLineEdit *cameraRotationTxt;
    QLabel *cameraZoomLbl;
    QLineEdit *cameraZoomTxt;
    QLabel *cameraPanLbl;
    QLineEdit *cameraPanTxt;
    QDialogButtonBox *buttonBox;
    QGroupBox *snapsGroup;
    QGridLayout *gridLayout_2;
    QLabel *gridSnapLbl;
    QLineEdit *gridSnapTxt;
    QLabel *angleSnapLbl;
    QLineEdit *angleSnapTxt;
    QCheckBox *useGridCheckBox;
    QCheckBox *useAngleCheckBox;

    void setupUi(QWidget *MapEditorPreferencesDialog)
    {
        if (MapEditorPreferencesDialog->objectName().isEmpty())
            MapEditorPreferencesDialog->setObjectName(QStringLiteral("MapEditorPreferencesDialog"));
        MapEditorPreferencesDialog->resize(383, 204);
        MapEditorPreferencesDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        movementSpeedsGroup = new QGroupBox(MapEditorPreferencesDialog);
        movementSpeedsGroup->setObjectName(QStringLiteral("movementSpeedsGroup"));
        movementSpeedsGroup->setGeometry(QRect(10, 10, 191, 151));
        gridLayout = new QGridLayout(movementSpeedsGroup);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        objectRotationLbl = new QLabel(movementSpeedsGroup);
        objectRotationLbl->setObjectName(QStringLiteral("objectRotationLbl"));

        gridLayout->addWidget(objectRotationLbl, 0, 0, 1, 1);

        objectRotationTxt = new QLineEdit(movementSpeedsGroup);
        objectRotationTxt->setObjectName(QStringLiteral("objectRotationTxt"));
        objectRotationTxt->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(objectRotationTxt, 0, 1, 1, 1);

        objectMoveLbl = new QLabel(movementSpeedsGroup);
        objectMoveLbl->setObjectName(QStringLiteral("objectMoveLbl"));

        gridLayout->addWidget(objectMoveLbl, 1, 0, 1, 1);

        objectMoveTxt = new QLineEdit(movementSpeedsGroup);
        objectMoveTxt->setObjectName(QStringLiteral("objectMoveTxt"));
        objectMoveTxt->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(objectMoveTxt, 1, 1, 1, 1);

        cameraRotationLbl = new QLabel(movementSpeedsGroup);
        cameraRotationLbl->setObjectName(QStringLiteral("cameraRotationLbl"));

        gridLayout->addWidget(cameraRotationLbl, 2, 0, 1, 1);

        cameraRotationTxt = new QLineEdit(movementSpeedsGroup);
        cameraRotationTxt->setObjectName(QStringLiteral("cameraRotationTxt"));
        cameraRotationTxt->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(cameraRotationTxt, 2, 1, 1, 1);

        cameraZoomLbl = new QLabel(movementSpeedsGroup);
        cameraZoomLbl->setObjectName(QStringLiteral("cameraZoomLbl"));

        gridLayout->addWidget(cameraZoomLbl, 3, 0, 1, 1);

        cameraZoomTxt = new QLineEdit(movementSpeedsGroup);
        cameraZoomTxt->setObjectName(QStringLiteral("cameraZoomTxt"));
        cameraZoomTxt->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(cameraZoomTxt, 3, 1, 1, 1);

        cameraPanLbl = new QLabel(movementSpeedsGroup);
        cameraPanLbl->setObjectName(QStringLiteral("cameraPanLbl"));

        gridLayout->addWidget(cameraPanLbl, 4, 0, 1, 1);

        cameraPanTxt = new QLineEdit(movementSpeedsGroup);
        cameraPanTxt->setObjectName(QStringLiteral("cameraPanTxt"));

        gridLayout->addWidget(cameraPanTxt, 4, 1, 1, 1);

        buttonBox = new QDialogButtonBox(MapEditorPreferencesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(200, 170, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        snapsGroup = new QGroupBox(MapEditorPreferencesDialog);
        snapsGroup->setObjectName(QStringLiteral("snapsGroup"));
        snapsGroup->setGeometry(QRect(210, 10, 161, 101));
        gridLayout_2 = new QGridLayout(snapsGroup);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridSnapLbl = new QLabel(snapsGroup);
        gridSnapLbl->setObjectName(QStringLiteral("gridSnapLbl"));

        gridLayout_2->addWidget(gridSnapLbl, 0, 0, 1, 1);

        gridSnapTxt = new QLineEdit(snapsGroup);
        gridSnapTxt->setObjectName(QStringLiteral("gridSnapTxt"));

        gridLayout_2->addWidget(gridSnapTxt, 0, 1, 1, 1);

        angleSnapLbl = new QLabel(snapsGroup);
        angleSnapLbl->setObjectName(QStringLiteral("angleSnapLbl"));

        gridLayout_2->addWidget(angleSnapLbl, 1, 0, 1, 1);

        angleSnapTxt = new QLineEdit(snapsGroup);
        angleSnapTxt->setObjectName(QStringLiteral("angleSnapTxt"));

        gridLayout_2->addWidget(angleSnapTxt, 1, 1, 1, 1);

        useGridCheckBox = new QCheckBox(snapsGroup);
        useGridCheckBox->setObjectName(QStringLiteral("useGridCheckBox"));
        useGridCheckBox->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(useGridCheckBox, 2, 0, 1, 1);

        useAngleCheckBox = new QCheckBox(snapsGroup);
        useAngleCheckBox->setObjectName(QStringLiteral("useAngleCheckBox"));
        useAngleCheckBox->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(useAngleCheckBox, 2, 1, 1, 1);


        retranslateUi(MapEditorPreferencesDialog);

        QMetaObject::connectSlotsByName(MapEditorPreferencesDialog);
    } // setupUi

    void retranslateUi(QWidget *MapEditorPreferencesDialog)
    {
        MapEditorPreferencesDialog->setWindowTitle(QApplication::translate("MapEditorPreferencesDialog", "Map editor preferences", Q_NULLPTR));
        movementSpeedsGroup->setTitle(QApplication::translate("MapEditorPreferencesDialog", "Movement speeds (cm/s, degrees/s)", Q_NULLPTR));
        objectRotationLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "Object rotation", Q_NULLPTR));
        objectMoveLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "Object move", Q_NULLPTR));
        cameraRotationLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "Camera rotation", Q_NULLPTR));
        cameraZoomLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "Camera zoom", Q_NULLPTR));
        cameraPanLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "Camera pan", Q_NULLPTR));
        snapsGroup->setTitle(QApplication::translate("MapEditorPreferencesDialog", "Snaps (cm, degrees)", Q_NULLPTR));
        gridSnapLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "Grid snap", Q_NULLPTR));
        angleSnapLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "Angle snap", Q_NULLPTR));
        useGridCheckBox->setText(QApplication::translate("MapEditorPreferencesDialog", "Use grid", Q_NULLPTR));
        useAngleCheckBox->setText(QApplication::translate("MapEditorPreferencesDialog", "Use angle", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MapEditorPreferencesDialog: public Ui_MapEditorPreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITORPREFERENCESDIALOG_H
