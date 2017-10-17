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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameEditorClass
{
public:
    QAction *actionObjConverter;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QTabWidget *tabWidget;
    QWidget *tab_11;
    QGridLayout *gridLayout_5;
    QWidget *tab_12;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuMeshConverter;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *GameEditorClass)
    {
        if (GameEditorClass->objectName().isEmpty())
            GameEditorClass->setObjectName(QStringLiteral("GameEditorClass"));
        GameEditorClass->resize(792, 399);
        actionObjConverter = new QAction(GameEditorClass);
        actionObjConverter->setObjectName(QStringLiteral("actionObjConverter"));
        centralWidget = new QWidget(GameEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));

        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab_11 = new QWidget();
        tab_11->setObjectName(QStringLiteral("tab_11"));
        gridLayout_5 = new QGridLayout(tab_11);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        tabWidget->addTab(tab_11, QString());
        tab_12 = new QWidget();
        tab_12->setObjectName(QStringLiteral("tab_12"));
        tabWidget->addTab(tab_12, QString());

        gridLayout_3->addWidget(tabWidget, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 0, 0, 1, 1);

        GameEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 792, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuMeshConverter = new QMenu(menuBar);
        menuMeshConverter->setObjectName(QStringLiteral("menuMeshConverter"));
        GameEditorClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(GameEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GameEditorClass->setStatusBar(statusBar);
        mainToolBar = new QToolBar(GameEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GameEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuMeshConverter->menuAction());
        menuMeshConverter->addAction(actionObjConverter);

        retranslateUi(GameEditorClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GameEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *GameEditorClass)
    {
        GameEditorClass->setWindowTitle(QApplication::translate("GameEditorClass", "GameEditor", Q_NULLPTR));
        actionObjConverter->setText(QApplication::translate("GameEditorClass", ".obj convert", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_11), QApplication::translate("GameEditorClass", "\320\241\321\202\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \320\270\320\263\321\200\320\276\320\262\321\213\320\265 \320\276\320\261\321\212\320\265\320\272\321\202\321\213", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_12), QApplication::translate("GameEditorClass", "Tab 2", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("GameEditorClass", "File", Q_NULLPTR));
        menuMeshConverter->setTitle(QApplication::translate("GameEditorClass", "Model converter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GameEditorClass: public Ui_GameEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEEDITOR_H
