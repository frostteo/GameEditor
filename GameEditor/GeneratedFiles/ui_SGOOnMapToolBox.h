/********************************************************************************
** Form generated from reading UI file 'SGOOnMapToolBox.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SGOONMAPTOOLBOX_H
#define UI_SGOONMAPTOOLBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SGOOnMapToolBox
{
public:
    QVBoxLayout *verticalLayout;
    QToolBox *SGOOnMapToolBox_2;
    QWidget *editPage;
    QPushButton *editBtn;
    QPushButton *cloneBtn;
    QPushButton *deleteBtn;
    QWidget *filterPage;
    QLabel *SGONameFilterLbl;
    QLabel *instanceNameLbl;
    QLineEdit *SGONameFilterTxt;
    QLineEdit *instanceNameFilterTxt;

    void setupUi(QWidget *SGOOnMapToolBox)
    {
        if (SGOOnMapToolBox->objectName().isEmpty())
            SGOOnMapToolBox->setObjectName(QStringLiteral("SGOOnMapToolBox"));
        SGOOnMapToolBox->resize(151, 192);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SGOOnMapToolBox->sizePolicy().hasHeightForWidth());
        SGOOnMapToolBox->setSizePolicy(sizePolicy);
        SGOOnMapToolBox->setMinimumSize(QSize(150, 190));
        verticalLayout = new QVBoxLayout(SGOOnMapToolBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        SGOOnMapToolBox_2 = new QToolBox(SGOOnMapToolBox);
        SGOOnMapToolBox_2->setObjectName(QStringLiteral("SGOOnMapToolBox_2"));
        editPage = new QWidget();
        editPage->setObjectName(QStringLiteral("editPage"));
        editPage->setGeometry(QRect(0, 0, 133, 120));
        editBtn = new QPushButton(editPage);
        editBtn->setObjectName(QStringLiteral("editBtn"));
        editBtn->setGeometry(QRect(10, 30, 75, 23));
        cloneBtn = new QPushButton(editPage);
        cloneBtn->setObjectName(QStringLiteral("cloneBtn"));
        cloneBtn->setGeometry(QRect(10, 0, 75, 23));
        deleteBtn = new QPushButton(editPage);
        deleteBtn->setObjectName(QStringLiteral("deleteBtn"));
        deleteBtn->setGeometry(QRect(10, 60, 75, 23));
        SGOOnMapToolBox_2->addItem(editPage, QStringLiteral("Edit"));
        filterPage = new QWidget();
        filterPage->setObjectName(QStringLiteral("filterPage"));
        filterPage->setGeometry(QRect(0, 0, 133, 120));
        SGONameFilterLbl = new QLabel(filterPage);
        SGONameFilterLbl->setObjectName(QStringLiteral("SGONameFilterLbl"));
        SGONameFilterLbl->setGeometry(QRect(0, 0, 50, 13));
        instanceNameLbl = new QLabel(filterPage);
        instanceNameLbl->setObjectName(QStringLiteral("instanceNameLbl"));
        instanceNameLbl->setGeometry(QRect(0, 50, 69, 13));
        SGONameFilterTxt = new QLineEdit(filterPage);
        SGONameFilterTxt->setObjectName(QStringLiteral("SGONameFilterTxt"));
        SGONameFilterTxt->setGeometry(QRect(0, 20, 121, 20));
        instanceNameFilterTxt = new QLineEdit(filterPage);
        instanceNameFilterTxt->setObjectName(QStringLiteral("instanceNameFilterTxt"));
        instanceNameFilterTxt->setGeometry(QRect(0, 70, 121, 20));
        SGOOnMapToolBox_2->addItem(filterPage, QStringLiteral("Filter"));

        verticalLayout->addWidget(SGOOnMapToolBox_2);


        retranslateUi(SGOOnMapToolBox);

        SGOOnMapToolBox_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SGOOnMapToolBox);
    } // setupUi

    void retranslateUi(QWidget *SGOOnMapToolBox)
    {
        SGOOnMapToolBox->setWindowTitle(QApplication::translate("SGOOnMapToolBox", "SGOOnMapToolBox", Q_NULLPTR));
        editBtn->setText(QApplication::translate("SGOOnMapToolBox", "edit", Q_NULLPTR));
        cloneBtn->setText(QApplication::translate("SGOOnMapToolBox", "clone", Q_NULLPTR));
        deleteBtn->setText(QApplication::translate("SGOOnMapToolBox", "delete", Q_NULLPTR));
        SGOOnMapToolBox_2->setItemText(SGOOnMapToolBox_2->indexOf(editPage), QApplication::translate("SGOOnMapToolBox", "Edit", Q_NULLPTR));
        SGONameFilterLbl->setText(QApplication::translate("SGOOnMapToolBox", "SGO name", Q_NULLPTR));
        instanceNameLbl->setText(QApplication::translate("SGOOnMapToolBox", "instance name", Q_NULLPTR));
        SGOOnMapToolBox_2->setItemText(SGOOnMapToolBox_2->indexOf(filterPage), QApplication::translate("SGOOnMapToolBox", "Filter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SGOOnMapToolBox: public Ui_SGOOnMapToolBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SGOONMAPTOOLBOX_H
