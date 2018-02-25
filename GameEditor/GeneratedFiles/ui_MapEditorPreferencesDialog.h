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
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QLabel *redAmbientColorLbl;
    QLabel *greenAmbientColorLbl;
    QLabel *blueAmbientColorLbl;
    QLineEdit *redAmbientColorTxt;
    QLineEdit *greenAmbientColorTxt;
    QLineEdit *blueAmbientColorTxt;
    QGroupBox *groupBox_3;
    QLabel *redDirectColorLbl;
    QLabel *greenDirectColorLbl;
    QLabel *blueDirectColorLbl;
    QLineEdit *redDirectLightColorTxt;
    QLineEdit *greenDirectLightColorTxt;
    QLineEdit *blueDirectLightColorTxt;
    QGroupBox *groupBox_4;
    QLabel *xDirectLightDirLbl;
    QLabel *yDirectLightDirLbl;
    QLabel *zDirectLightDirLbl;
    QLineEdit *xDirectLightDirTxt;
    QLineEdit *yDirectLightDirTxt;
    QLineEdit *zDirectLightDirTxt;
    QCheckBox *useTestLightiningCheckBox;
    QGroupBox *groupBox_5;
    QGroupBox *groupBox_6;
    QLabel *redRealAmbientLbl;
    QLabel *greenRealAmbientLbl;
    QLabel *blueRealAmbientLbl;
    QLineEdit *realRedAmbientTxt;
    QLineEdit *realGreenAmbientTxt;
    QLineEdit *realBlueAmbientTxt;
    QLabel *radiusOfAddingPointLightToRenderLbl;
    QLineEdit *radiusOfAddingPointLightToRenderTxt;

    void setupUi(QWidget *MapEditorPreferencesDialog)
    {
        if (MapEditorPreferencesDialog->objectName().isEmpty())
            MapEditorPreferencesDialog->setObjectName(QStringLiteral("MapEditorPreferencesDialog"));
        MapEditorPreferencesDialog->resize(383, 571);
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
        buttonBox->setGeometry(QRect(220, 540, 156, 23));
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

        groupBox = new QGroupBox(MapEditorPreferencesDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 170, 271, 231));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 20, 251, 51));
        redAmbientColorLbl = new QLabel(groupBox_2);
        redAmbientColorLbl->setObjectName(QStringLiteral("redAmbientColorLbl"));
        redAmbientColorLbl->setGeometry(QRect(10, 20, 16, 16));
        greenAmbientColorLbl = new QLabel(groupBox_2);
        greenAmbientColorLbl->setObjectName(QStringLiteral("greenAmbientColorLbl"));
        greenAmbientColorLbl->setGeometry(QRect(80, 20, 31, 16));
        blueAmbientColorLbl = new QLabel(groupBox_2);
        blueAmbientColorLbl->setObjectName(QStringLiteral("blueAmbientColorLbl"));
        blueAmbientColorLbl->setGeometry(QRect(170, 20, 21, 16));
        redAmbientColorTxt = new QLineEdit(groupBox_2);
        redAmbientColorTxt->setObjectName(QStringLiteral("redAmbientColorTxt"));
        redAmbientColorTxt->setGeometry(QRect(30, 20, 41, 20));
        greenAmbientColorTxt = new QLineEdit(groupBox_2);
        greenAmbientColorTxt->setObjectName(QStringLiteral("greenAmbientColorTxt"));
        greenAmbientColorTxt->setGeometry(QRect(120, 20, 41, 20));
        blueAmbientColorTxt = new QLineEdit(groupBox_2);
        blueAmbientColorTxt->setObjectName(QStringLiteral("blueAmbientColorTxt"));
        blueAmbientColorTxt->setGeometry(QRect(200, 20, 41, 20));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 80, 251, 51));
        redDirectColorLbl = new QLabel(groupBox_3);
        redDirectColorLbl->setObjectName(QStringLiteral("redDirectColorLbl"));
        redDirectColorLbl->setGeometry(QRect(10, 20, 16, 16));
        greenDirectColorLbl = new QLabel(groupBox_3);
        greenDirectColorLbl->setObjectName(QStringLiteral("greenDirectColorLbl"));
        greenDirectColorLbl->setGeometry(QRect(80, 20, 31, 16));
        blueDirectColorLbl = new QLabel(groupBox_3);
        blueDirectColorLbl->setObjectName(QStringLiteral("blueDirectColorLbl"));
        blueDirectColorLbl->setGeometry(QRect(170, 20, 21, 16));
        redDirectLightColorTxt = new QLineEdit(groupBox_3);
        redDirectLightColorTxt->setObjectName(QStringLiteral("redDirectLightColorTxt"));
        redDirectLightColorTxt->setGeometry(QRect(30, 20, 41, 20));
        greenDirectLightColorTxt = new QLineEdit(groupBox_3);
        greenDirectLightColorTxt->setObjectName(QStringLiteral("greenDirectLightColorTxt"));
        greenDirectLightColorTxt->setGeometry(QRect(120, 20, 41, 20));
        blueDirectLightColorTxt = new QLineEdit(groupBox_3);
        blueDirectLightColorTxt->setObjectName(QStringLiteral("blueDirectLightColorTxt"));
        blueDirectLightColorTxt->setGeometry(QRect(200, 20, 41, 20));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 140, 251, 51));
        xDirectLightDirLbl = new QLabel(groupBox_4);
        xDirectLightDirLbl->setObjectName(QStringLiteral("xDirectLightDirLbl"));
        xDirectLightDirLbl->setGeometry(QRect(20, 20, 16, 16));
        yDirectLightDirLbl = new QLabel(groupBox_4);
        yDirectLightDirLbl->setObjectName(QStringLiteral("yDirectLightDirLbl"));
        yDirectLightDirLbl->setGeometry(QRect(110, 20, 16, 16));
        zDirectLightDirLbl = new QLabel(groupBox_4);
        zDirectLightDirLbl->setObjectName(QStringLiteral("zDirectLightDirLbl"));
        zDirectLightDirLbl->setGeometry(QRect(190, 20, 16, 16));
        xDirectLightDirTxt = new QLineEdit(groupBox_4);
        xDirectLightDirTxt->setObjectName(QStringLiteral("xDirectLightDirTxt"));
        xDirectLightDirTxt->setGeometry(QRect(30, 20, 41, 20));
        yDirectLightDirTxt = new QLineEdit(groupBox_4);
        yDirectLightDirTxt->setObjectName(QStringLiteral("yDirectLightDirTxt"));
        yDirectLightDirTxt->setGeometry(QRect(120, 20, 41, 20));
        zDirectLightDirTxt = new QLineEdit(groupBox_4);
        zDirectLightDirTxt->setObjectName(QStringLiteral("zDirectLightDirTxt"));
        zDirectLightDirTxt->setGeometry(QRect(200, 20, 41, 20));
        useTestLightiningCheckBox = new QCheckBox(groupBox);
        useTestLightiningCheckBox->setObjectName(QStringLiteral("useTestLightiningCheckBox"));
        useTestLightiningCheckBox->setGeometry(QRect(70, 200, 111, 20));
        useTestLightiningCheckBox->setLayoutDirection(Qt::RightToLeft);
        useTestLightiningCheckBox->setChecked(true);
        groupBox_5 = new QGroupBox(MapEditorPreferencesDialog);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 410, 271, 121));
        groupBox_6 = new QGroupBox(groupBox_5);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 20, 251, 51));
        redRealAmbientLbl = new QLabel(groupBox_6);
        redRealAmbientLbl->setObjectName(QStringLiteral("redRealAmbientLbl"));
        redRealAmbientLbl->setGeometry(QRect(10, 20, 16, 16));
        greenRealAmbientLbl = new QLabel(groupBox_6);
        greenRealAmbientLbl->setObjectName(QStringLiteral("greenRealAmbientLbl"));
        greenRealAmbientLbl->setGeometry(QRect(80, 20, 31, 16));
        blueRealAmbientLbl = new QLabel(groupBox_6);
        blueRealAmbientLbl->setObjectName(QStringLiteral("blueRealAmbientLbl"));
        blueRealAmbientLbl->setGeometry(QRect(170, 20, 21, 16));
        realRedAmbientTxt = new QLineEdit(groupBox_6);
        realRedAmbientTxt->setObjectName(QStringLiteral("realRedAmbientTxt"));
        realRedAmbientTxt->setGeometry(QRect(30, 20, 41, 20));
        realGreenAmbientTxt = new QLineEdit(groupBox_6);
        realGreenAmbientTxt->setObjectName(QStringLiteral("realGreenAmbientTxt"));
        realGreenAmbientTxt->setGeometry(QRect(120, 20, 41, 20));
        realBlueAmbientTxt = new QLineEdit(groupBox_6);
        realBlueAmbientTxt->setObjectName(QStringLiteral("realBlueAmbientTxt"));
        realBlueAmbientTxt->setGeometry(QRect(200, 20, 41, 20));
        radiusOfAddingPointLightToRenderLbl = new QLabel(groupBox_5);
        radiusOfAddingPointLightToRenderLbl->setObjectName(QStringLiteral("radiusOfAddingPointLightToRenderLbl"));
        radiusOfAddingPointLightToRenderLbl->setGeometry(QRect(10, 80, 131, 31));
        radiusOfAddingPointLightToRenderLbl->setWordWrap(true);
        radiusOfAddingPointLightToRenderTxt = new QLineEdit(groupBox_5);
        radiusOfAddingPointLightToRenderTxt->setObjectName(QStringLiteral("radiusOfAddingPointLightToRenderTxt"));
        radiusOfAddingPointLightToRenderTxt->setGeometry(QRect(120, 90, 131, 20));
        QWidget::setTabOrder(objectRotationTxt, objectMoveTxt);
        QWidget::setTabOrder(objectMoveTxt, cameraRotationTxt);
        QWidget::setTabOrder(cameraRotationTxt, cameraZoomTxt);
        QWidget::setTabOrder(cameraZoomTxt, cameraPanTxt);
        QWidget::setTabOrder(cameraPanTxt, gridSnapTxt);
        QWidget::setTabOrder(gridSnapTxt, angleSnapTxt);
        QWidget::setTabOrder(angleSnapTxt, useGridCheckBox);
        QWidget::setTabOrder(useGridCheckBox, useAngleCheckBox);
        QWidget::setTabOrder(useAngleCheckBox, redAmbientColorTxt);
        QWidget::setTabOrder(redAmbientColorTxt, greenAmbientColorTxt);
        QWidget::setTabOrder(greenAmbientColorTxt, blueAmbientColorTxt);
        QWidget::setTabOrder(blueAmbientColorTxt, redDirectLightColorTxt);
        QWidget::setTabOrder(redDirectLightColorTxt, greenDirectLightColorTxt);
        QWidget::setTabOrder(greenDirectLightColorTxt, blueDirectLightColorTxt);
        QWidget::setTabOrder(blueDirectLightColorTxt, xDirectLightDirTxt);
        QWidget::setTabOrder(xDirectLightDirTxt, yDirectLightDirTxt);
        QWidget::setTabOrder(yDirectLightDirTxt, zDirectLightDirTxt);
        QWidget::setTabOrder(zDirectLightDirTxt, useTestLightiningCheckBox);

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
        groupBox->setTitle(QApplication::translate("MapEditorPreferencesDialog", "Editor environment test lightining", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MapEditorPreferencesDialog", "Ambient light color", Q_NULLPTR));
        redAmbientColorLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "red", Q_NULLPTR));
        greenAmbientColorLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "green", Q_NULLPTR));
        blueAmbientColorLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "blue", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MapEditorPreferencesDialog", "Direct light color", Q_NULLPTR));
        redDirectColorLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "red", Q_NULLPTR));
        greenDirectColorLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "green", Q_NULLPTR));
        blueDirectColorLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "blue", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MapEditorPreferencesDialog", "Direct light direction", Q_NULLPTR));
        xDirectLightDirLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "x", Q_NULLPTR));
        yDirectLightDirLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "y", Q_NULLPTR));
        zDirectLightDirLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "z", Q_NULLPTR));
        useTestLightiningCheckBox->setText(QApplication::translate("MapEditorPreferencesDialog", "Use test lightining", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MapEditorPreferencesDialog", "Environement lighting", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("MapEditorPreferencesDialog", "Ambient color", Q_NULLPTR));
        redRealAmbientLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "red", Q_NULLPTR));
        greenRealAmbientLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "green", Q_NULLPTR));
        blueRealAmbientLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "blue", Q_NULLPTR));
        radiusOfAddingPointLightToRenderLbl->setText(QApplication::translate("MapEditorPreferencesDialog", "Radius of adding light sources to the render", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MapEditorPreferencesDialog: public Ui_MapEditorPreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITORPREFERENCESDIALOG_H
