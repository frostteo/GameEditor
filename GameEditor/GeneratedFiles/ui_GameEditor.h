/********************************************************************************
** Form generated from reading UI file 'GameEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEEDITOR_H
#define UI_GAMEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameEditorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GameEditorClass)
    {
        if (GameEditorClass->objectName().isEmpty())
            GameEditorClass->setObjectName(QStringLiteral("GameEditorClass"));
        GameEditorClass->resize(600, 400);
        menuBar = new QMenuBar(GameEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        GameEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GameEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GameEditorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(GameEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GameEditorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GameEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GameEditorClass->setStatusBar(statusBar);

        retranslateUi(GameEditorClass);

        QMetaObject::connectSlotsByName(GameEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *GameEditorClass)
    {
        GameEditorClass->setWindowTitle(QApplication::translate("GameEditorClass", "GameEditor", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GameEditorClass: public Ui_GameEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEEDITOR_H
