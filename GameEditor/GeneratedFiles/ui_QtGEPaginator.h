/********************************************************************************
** Form generated from reading UI file 'QtGEPaginator.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGEPAGINATOR_H
#define UI_QTGEPAGINATOR_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGEPaginator
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *firstBtn;
    QPushButton *prevBtn;
    QLabel *pageLbl;
    QLineEdit *pageTxt;
    QLabel *ofLbl;
    QLineEdit *countTxt;
    QPushButton *nextBtn;
    QPushButton *lastBtn;
    QLabel *onPageLbl;
    QComboBox *onPageList;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *QtGEPaginator)
    {
        if (QtGEPaginator->objectName().isEmpty())
            QtGEPaginator->setObjectName(QStringLiteral("QtGEPaginator"));
        QtGEPaginator->resize(626, 45);
        QtGEPaginator->setMinimumSize(QSize(626, 0));
        gridLayout = new QGridLayout(QtGEPaginator);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        firstBtn = new QPushButton(QtGEPaginator);
        firstBtn->setObjectName(QStringLiteral("firstBtn"));

        horizontalLayout->addWidget(firstBtn);

        prevBtn = new QPushButton(QtGEPaginator);
        prevBtn->setObjectName(QStringLiteral("prevBtn"));

        horizontalLayout->addWidget(prevBtn);

        pageLbl = new QLabel(QtGEPaginator);
        pageLbl->setObjectName(QStringLiteral("pageLbl"));

        horizontalLayout->addWidget(pageLbl);

        pageTxt = new QLineEdit(QtGEPaginator);
        pageTxt->setObjectName(QStringLiteral("pageTxt"));
        pageTxt->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(pageTxt);

        ofLbl = new QLabel(QtGEPaginator);
        ofLbl->setObjectName(QStringLiteral("ofLbl"));

        horizontalLayout->addWidget(ofLbl);

        countTxt = new QLineEdit(QtGEPaginator);
        countTxt->setObjectName(QStringLiteral("countTxt"));
        countTxt->setEnabled(true);
        countTxt->setMaximumSize(QSize(50, 16777215));
        countTxt->setReadOnly(true);

        horizontalLayout->addWidget(countTxt);

        nextBtn = new QPushButton(QtGEPaginator);
        nextBtn->setObjectName(QStringLiteral("nextBtn"));

        horizontalLayout->addWidget(nextBtn);

        lastBtn = new QPushButton(QtGEPaginator);
        lastBtn->setObjectName(QStringLiteral("lastBtn"));

        horizontalLayout->addWidget(lastBtn);

        onPageLbl = new QLabel(QtGEPaginator);
        onPageLbl->setObjectName(QStringLiteral("onPageLbl"));

        horizontalLayout->addWidget(onPageLbl);

        onPageList = new QComboBox(QtGEPaginator);
        onPageList->setObjectName(QStringLiteral("onPageList"));

        horizontalLayout->addWidget(onPageList);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(QtGEPaginator);

        QMetaObject::connectSlotsByName(QtGEPaginator);
    } // setupUi

    void retranslateUi(QWidget *QtGEPaginator)
    {
        QtGEPaginator->setWindowTitle(QApplication::translate("QtGEPaginator", "QtGEPaginator", Q_NULLPTR));
        firstBtn->setText(QApplication::translate("QtGEPaginator", "first", Q_NULLPTR));
        prevBtn->setText(QApplication::translate("QtGEPaginator", "prev", Q_NULLPTR));
        pageLbl->setText(QApplication::translate("QtGEPaginator", "page", Q_NULLPTR));
        ofLbl->setText(QApplication::translate("QtGEPaginator", "of", Q_NULLPTR));
        nextBtn->setText(QApplication::translate("QtGEPaginator", "next", Q_NULLPTR));
        lastBtn->setText(QApplication::translate("QtGEPaginator", "last", Q_NULLPTR));
        onPageLbl->setText(QApplication::translate("QtGEPaginator", "on page:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGEPaginator: public Ui_QtGEPaginator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGEPAGINATOR_H
