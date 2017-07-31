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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameEditorClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab_11;
    QGridLayout *gridLayout_5;
    QTableView *staticGOTableView;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *addStaticGOBtn;
    QPushButton *editStaticGOBtn;
    QPushButton *deleteStaticGOBtn;
    QPushButton *previewStaticGOBtn;
    QWidget *tab_12;
    QWidget *widget;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *GameEditorClass)
    {
        if (GameEditorClass->objectName().isEmpty())
            GameEditorClass->setObjectName(QStringLiteral("GameEditorClass"));
        GameEditorClass->resize(601, 400);
        centralWidget = new QWidget(GameEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_11 = new QWidget();
        tab_11->setObjectName(QStringLiteral("tab_11"));
        gridLayout_5 = new QGridLayout(tab_11);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        staticGOTableView = new QTableView(tab_11);
        staticGOTableView->setObjectName(QStringLiteral("staticGOTableView"));

        gridLayout_5->addWidget(staticGOTableView, 1, 0, 1, 1);

        groupBox = new QGroupBox(tab_11);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        addStaticGOBtn = new QPushButton(groupBox);
        addStaticGOBtn->setObjectName(QStringLiteral("addStaticGOBtn"));

        horizontalLayout->addWidget(addStaticGOBtn);

        editStaticGOBtn = new QPushButton(groupBox);
        editStaticGOBtn->setObjectName(QStringLiteral("editStaticGOBtn"));
        editStaticGOBtn->setEnabled(false);
        editStaticGOBtn->setCheckable(false);

        horizontalLayout->addWidget(editStaticGOBtn);

        deleteStaticGOBtn = new QPushButton(groupBox);
        deleteStaticGOBtn->setObjectName(QStringLiteral("deleteStaticGOBtn"));
        deleteStaticGOBtn->setEnabled(false);

        horizontalLayout->addWidget(deleteStaticGOBtn);

        previewStaticGOBtn = new QPushButton(groupBox);
        previewStaticGOBtn->setObjectName(QStringLiteral("previewStaticGOBtn"));
        previewStaticGOBtn->setEnabled(false);

        horizontalLayout->addWidget(previewStaticGOBtn);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        tabWidget->addTab(tab_11, QString());
        tab_12 = new QWidget();
        tab_12->setObjectName(QStringLiteral("tab_12"));
        tabWidget->addTab(tab_12, QString());

        gridLayout_3->addWidget(tabWidget, 1, 0, 1, 1);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));

        gridLayout_3->addWidget(widget, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 0, 0, 1, 1);

        GameEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 601, 21));
        GameEditorClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(GameEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GameEditorClass->setStatusBar(statusBar);
        mainToolBar = new QToolBar(GameEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GameEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(GameEditorClass);

        QMetaObject::connectSlotsByName(GameEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *GameEditorClass)
    {
        GameEditorClass->setWindowTitle(QApplication::translate("GameEditorClass", "GameEditor", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("GameEditorClass", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", Q_NULLPTR));
        addStaticGOBtn->setText(QApplication::translate("GameEditorClass", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        editStaticGOBtn->setText(QApplication::translate("GameEditorClass", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", Q_NULLPTR));
        deleteStaticGOBtn->setText(QApplication::translate("GameEditorClass", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", Q_NULLPTR));
        previewStaticGOBtn->setText(QApplication::translate("GameEditorClass", "\320\237\321\200\320\276\321\201\320\274\320\276\321\202\321\200", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_11), QApplication::translate("GameEditorClass", "\320\241\321\202\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \320\270\320\263\321\200\320\276\320\262\321\213\320\265 \320\276\320\261\321\212\320\265\320\272\321\202\321\213", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_12), QApplication::translate("GameEditorClass", "Tab 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GameEditorClass: public Ui_GameEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEEDITOR_H
