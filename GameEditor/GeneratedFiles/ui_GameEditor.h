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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameEditorClass
{
public:
    QAction *actionObjConverter;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab_11;
    QGridLayout *gridLayout_5;
    QTableView *staticGOTableView;
    QToolBox *toolBox;
    QWidget *editToolPageSGOTable;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *addStaticGOBtn;
    QPushButton *editStaticGOBtn;
    QPushButton *deleteStaticGOBtn;
    QPushButton *previewStaticGOBtn;
    QWidget *filterToolPageSGOTable;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *filterSGONameLbl;
    QLineEdit *filterSGONameTxt;
    QLabel *filterSGOModelLbl;
    QLineEdit *filterSGOModelTxt;
    QLabel *filterSGOMaterialLbl;
    QLineEdit *filterSGOMaterialTxt;
    QWidget *paginationWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *SGOTableFirstPageBtn;
    QPushButton *SGOTablePrevPageBtn;
    QLabel *SGOTablePageLbl;
    QLineEdit *SGOTablePageTxt;
    QLabel *SGOTableOfLbl;
    QLineEdit *SGOTablePageCountTxt;
    QPushButton *SGOTableNextBtn;
    QPushButton *SGOTableLastBtn;
    QComboBox *SGOTableOrdrerDir;
    QComboBox *SGOTableSortField;
    QLabel *SGOTableOnPageLbl;
    QComboBox *SGOTableOnPage;
    QWidget *tab_12;
    QWidget *widget1;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuMeshConverter;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *GameEditorClass)
    {
        if (GameEditorClass->objectName().isEmpty())
            GameEditorClass->setObjectName(QStringLiteral("GameEditorClass"));
        GameEditorClass->resize(656, 399);
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

        toolBox = new QToolBox(tab_11);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolBox->sizePolicy().hasHeightForWidth());
        toolBox->setSizePolicy(sizePolicy);
        toolBox->setMinimumSize(QSize(0, 80));
        toolBox->setMaximumSize(QSize(16777215, 80));
        editToolPageSGOTable = new QWidget();
        editToolPageSGOTable->setObjectName(QStringLiteral("editToolPageSGOTable"));
        editToolPageSGOTable->setGeometry(QRect(0, 0, 612, 26));
        layoutWidget = new QWidget(editToolPageSGOTable);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 332, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        addStaticGOBtn = new QPushButton(layoutWidget);
        addStaticGOBtn->setObjectName(QStringLiteral("addStaticGOBtn"));

        horizontalLayout->addWidget(addStaticGOBtn);

        editStaticGOBtn = new QPushButton(layoutWidget);
        editStaticGOBtn->setObjectName(QStringLiteral("editStaticGOBtn"));
        editStaticGOBtn->setEnabled(false);
        editStaticGOBtn->setCheckable(false);

        horizontalLayout->addWidget(editStaticGOBtn);

        deleteStaticGOBtn = new QPushButton(layoutWidget);
        deleteStaticGOBtn->setObjectName(QStringLiteral("deleteStaticGOBtn"));
        deleteStaticGOBtn->setEnabled(false);

        horizontalLayout->addWidget(deleteStaticGOBtn);

        previewStaticGOBtn = new QPushButton(layoutWidget);
        previewStaticGOBtn->setObjectName(QStringLiteral("previewStaticGOBtn"));
        previewStaticGOBtn->setEnabled(false);

        horizontalLayout->addWidget(previewStaticGOBtn);

        toolBox->addItem(editToolPageSGOTable, QStringLiteral("Edit"));
        filterToolPageSGOTable = new QWidget();
        filterToolPageSGOTable->setObjectName(QStringLiteral("filterToolPageSGOTable"));
        filterToolPageSGOTable->setGeometry(QRect(0, 0, 612, 26));
        widget = new QWidget(filterToolPageSGOTable);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 0, 523, 22));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        filterSGONameLbl = new QLabel(widget);
        filterSGONameLbl->setObjectName(QStringLiteral("filterSGONameLbl"));

        horizontalLayout_3->addWidget(filterSGONameLbl);

        filterSGONameTxt = new QLineEdit(widget);
        filterSGONameTxt->setObjectName(QStringLiteral("filterSGONameTxt"));

        horizontalLayout_3->addWidget(filterSGONameTxt);

        filterSGOModelLbl = new QLabel(widget);
        filterSGOModelLbl->setObjectName(QStringLiteral("filterSGOModelLbl"));

        horizontalLayout_3->addWidget(filterSGOModelLbl);

        filterSGOModelTxt = new QLineEdit(widget);
        filterSGOModelTxt->setObjectName(QStringLiteral("filterSGOModelTxt"));

        horizontalLayout_3->addWidget(filterSGOModelTxt);

        filterSGOMaterialLbl = new QLabel(widget);
        filterSGOMaterialLbl->setObjectName(QStringLiteral("filterSGOMaterialLbl"));

        horizontalLayout_3->addWidget(filterSGOMaterialLbl);

        filterSGOMaterialTxt = new QLineEdit(widget);
        filterSGOMaterialTxt->setObjectName(QStringLiteral("filterSGOMaterialTxt"));

        horizontalLayout_3->addWidget(filterSGOMaterialTxt);

        toolBox->addItem(filterToolPageSGOTable, QStringLiteral("Filter"));

        gridLayout_5->addWidget(toolBox, 0, 0, 1, 1);

        paginationWidget = new QWidget(tab_11);
        paginationWidget->setObjectName(QStringLiteral("paginationWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(paginationWidget->sizePolicy().hasHeightForWidth());
        paginationWidget->setSizePolicy(sizePolicy1);
        paginationWidget->setMinimumSize(QSize(0, 48));
        paginationWidget->setMaximumSize(QSize(16777215, 50));
        gridLayout_2 = new QGridLayout(paginationWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        SGOTableFirstPageBtn = new QPushButton(paginationWidget);
        SGOTableFirstPageBtn->setObjectName(QStringLiteral("SGOTableFirstPageBtn"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(SGOTableFirstPageBtn->sizePolicy().hasHeightForWidth());
        SGOTableFirstPageBtn->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(SGOTableFirstPageBtn);

        SGOTablePrevPageBtn = new QPushButton(paginationWidget);
        SGOTablePrevPageBtn->setObjectName(QStringLiteral("SGOTablePrevPageBtn"));
        sizePolicy2.setHeightForWidth(SGOTablePrevPageBtn->sizePolicy().hasHeightForWidth());
        SGOTablePrevPageBtn->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(SGOTablePrevPageBtn);

        SGOTablePageLbl = new QLabel(paginationWidget);
        SGOTablePageLbl->setObjectName(QStringLiteral("SGOTablePageLbl"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(SGOTablePageLbl->sizePolicy().hasHeightForWidth());
        SGOTablePageLbl->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(SGOTablePageLbl);

        SGOTablePageTxt = new QLineEdit(paginationWidget);
        SGOTablePageTxt->setObjectName(QStringLiteral("SGOTablePageTxt"));
        sizePolicy2.setHeightForWidth(SGOTablePageTxt->sizePolicy().hasHeightForWidth());
        SGOTablePageTxt->setSizePolicy(sizePolicy2);
        SGOTablePageTxt->setMinimumSize(QSize(50, 0));
        SGOTablePageTxt->setMaximumSize(QSize(50, 16777215));
        SGOTablePageTxt->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(SGOTablePageTxt);

        SGOTableOfLbl = new QLabel(paginationWidget);
        SGOTableOfLbl->setObjectName(QStringLiteral("SGOTableOfLbl"));
        sizePolicy3.setHeightForWidth(SGOTableOfLbl->sizePolicy().hasHeightForWidth());
        SGOTableOfLbl->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(SGOTableOfLbl);

        SGOTablePageCountTxt = new QLineEdit(paginationWidget);
        SGOTablePageCountTxt->setObjectName(QStringLiteral("SGOTablePageCountTxt"));
        SGOTablePageCountTxt->setEnabled(true);
        sizePolicy2.setHeightForWidth(SGOTablePageCountTxt->sizePolicy().hasHeightForWidth());
        SGOTablePageCountTxt->setSizePolicy(sizePolicy2);
        SGOTablePageCountTxt->setMinimumSize(QSize(50, 0));
        SGOTablePageCountTxt->setMaximumSize(QSize(50, 16777215));
        SGOTablePageCountTxt->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SGOTablePageCountTxt->setReadOnly(true);

        horizontalLayout_2->addWidget(SGOTablePageCountTxt);

        SGOTableNextBtn = new QPushButton(paginationWidget);
        SGOTableNextBtn->setObjectName(QStringLiteral("SGOTableNextBtn"));
        sizePolicy2.setHeightForWidth(SGOTableNextBtn->sizePolicy().hasHeightForWidth());
        SGOTableNextBtn->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(SGOTableNextBtn);

        SGOTableLastBtn = new QPushButton(paginationWidget);
        SGOTableLastBtn->setObjectName(QStringLiteral("SGOTableLastBtn"));
        sizePolicy2.setHeightForWidth(SGOTableLastBtn->sizePolicy().hasHeightForWidth());
        SGOTableLastBtn->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(SGOTableLastBtn);

        SGOTableOrdrerDir = new QComboBox(paginationWidget);
        SGOTableOrdrerDir->setObjectName(QStringLiteral("SGOTableOrdrerDir"));
        sizePolicy2.setHeightForWidth(SGOTableOrdrerDir->sizePolicy().hasHeightForWidth());
        SGOTableOrdrerDir->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(SGOTableOrdrerDir);

        SGOTableSortField = new QComboBox(paginationWidget);
        SGOTableSortField->setObjectName(QStringLiteral("SGOTableSortField"));
        sizePolicy2.setHeightForWidth(SGOTableSortField->sizePolicy().hasHeightForWidth());
        SGOTableSortField->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(SGOTableSortField);

        SGOTableOnPageLbl = new QLabel(paginationWidget);
        SGOTableOnPageLbl->setObjectName(QStringLiteral("SGOTableOnPageLbl"));
        sizePolicy3.setHeightForWidth(SGOTableOnPageLbl->sizePolicy().hasHeightForWidth());
        SGOTableOnPageLbl->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(SGOTableOnPageLbl);

        SGOTableOnPage = new QComboBox(paginationWidget);
        SGOTableOnPage->setObjectName(QStringLiteral("SGOTableOnPage"));
        sizePolicy2.setHeightForWidth(SGOTableOnPage->sizePolicy().hasHeightForWidth());
        SGOTableOnPage->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(SGOTableOnPage);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        gridLayout_5->addWidget(paginationWidget, 2, 0, 1, 1);

        tabWidget->addTab(tab_11, QString());
        tab_12 = new QWidget();
        tab_12->setObjectName(QStringLiteral("tab_12"));
        tabWidget->addTab(tab_12, QString());

        gridLayout_3->addWidget(tabWidget, 1, 0, 1, 1);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QStringLiteral("widget1"));

        gridLayout_3->addWidget(widget1, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 0, 0, 1, 1);

        GameEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 656, 21));
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
        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(GameEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *GameEditorClass)
    {
        GameEditorClass->setWindowTitle(QApplication::translate("GameEditorClass", "GameEditor", Q_NULLPTR));
        actionObjConverter->setText(QApplication::translate("GameEditorClass", ".obj convert", Q_NULLPTR));
        addStaticGOBtn->setText(QApplication::translate("GameEditorClass", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        editStaticGOBtn->setText(QApplication::translate("GameEditorClass", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", Q_NULLPTR));
        deleteStaticGOBtn->setText(QApplication::translate("GameEditorClass", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", Q_NULLPTR));
        previewStaticGOBtn->setText(QApplication::translate("GameEditorClass", "\320\237\321\200\320\276\321\201\320\274\320\276\321\202\321\200", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(editToolPageSGOTable), QApplication::translate("GameEditorClass", "Edit", Q_NULLPTR));
        filterSGONameLbl->setText(QApplication::translate("GameEditorClass", "name", Q_NULLPTR));
        filterSGOModelLbl->setText(QApplication::translate("GameEditorClass", "model", Q_NULLPTR));
        filterSGOMaterialLbl->setText(QApplication::translate("GameEditorClass", "material", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(filterToolPageSGOTable), QApplication::translate("GameEditorClass", "Filter", Q_NULLPTR));
        SGOTableFirstPageBtn->setText(QApplication::translate("GameEditorClass", "first", Q_NULLPTR));
        SGOTablePrevPageBtn->setText(QApplication::translate("GameEditorClass", "prev", Q_NULLPTR));
        SGOTablePageLbl->setText(QApplication::translate("GameEditorClass", "page", Q_NULLPTR));
        SGOTableOfLbl->setText(QApplication::translate("GameEditorClass", "of", Q_NULLPTR));
        SGOTableNextBtn->setText(QApplication::translate("GameEditorClass", "next", Q_NULLPTR));
        SGOTableLastBtn->setText(QApplication::translate("GameEditorClass", "last", Q_NULLPTR));
        SGOTableOrdrerDir->clear();
        SGOTableOrdrerDir->insertItems(0, QStringList()
         << QApplication::translate("GameEditorClass", "ASC", Q_NULLPTR)
         << QApplication::translate("GameEditorClass", "DESC", Q_NULLPTR)
        );
        SGOTableSortField->clear();
        SGOTableSortField->insertItems(0, QStringList()
         << QApplication::translate("GameEditorClass", "Id", Q_NULLPTR)
         << QApplication::translate("GameEditorClass", "name", Q_NULLPTR)
         << QApplication::translate("GameEditorClass", "model", Q_NULLPTR)
         << QApplication::translate("GameEditorClass", "material", Q_NULLPTR)
        );
        SGOTableOnPageLbl->setText(QApplication::translate("GameEditorClass", "on page:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_11), QApplication::translate("GameEditorClass", "\320\241\321\202\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \320\270\320\263\321\200\320\276\320\262\321\213\320\265 \320\276\320\261\321\212\320\265\320\272\321\202\321\213", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_12), QApplication::translate("GameEditorClass", "Tab 2", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("GameEditorClass", "File", Q_NULLPTR));
        menuMeshConverter->setTitle(QApplication::translate("GameEditorClass", "Mesh converter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GameEditorClass: public Ui_GameEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEEDITOR_H
