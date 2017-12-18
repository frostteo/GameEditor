/********************************************************************************
** Form generated from reading UI file 'PointLightWidgetToolBox.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POINTLIGHTWIDGETTOOLBOX_H
#define UI_POINTLIGHTWIDGETTOOLBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PointLightWidgetToolBox
{
public:
    QToolBox *pointLightToolBox;
    QWidget *editTool;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *addBtn;
    QPushButton *editBtn;
    QPushButton *deleteBtn;
    QPushButton *configureRelPosBtn;
    QPushButton *addToMapBtn;
    QWidget *filterTool;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *nameLbl;
    QLineEdit *nameFilterTxt;
    QLabel *sgoNameLbl;
    QLineEdit *sgoNameFilterTxt;

    void setupUi(QWidget *PointLightWidgetToolBox)
    {
        if (PointLightWidgetToolBox->objectName().isEmpty())
            PointLightWidgetToolBox->setObjectName(QStringLiteral("PointLightWidgetToolBox"));
        PointLightWidgetToolBox->resize(144, 228);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PointLightWidgetToolBox->sizePolicy().hasHeightForWidth());
        PointLightWidgetToolBox->setSizePolicy(sizePolicy);
        PointLightWidgetToolBox->setMinimumSize(QSize(144, 228));
        pointLightToolBox = new QToolBox(PointLightWidgetToolBox);
        pointLightToolBox->setObjectName(QStringLiteral("pointLightToolBox"));
        pointLightToolBox->setGeometry(QRect(10, 10, 121, 201));
        editTool = new QWidget();
        editTool->setObjectName(QStringLiteral("editTool"));
        editTool->setGeometry(QRect(0, 0, 121, 147));
        layoutWidget = new QWidget(editTool);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 90, 141));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        addBtn = new QPushButton(layoutWidget);
        addBtn->setObjectName(QStringLiteral("addBtn"));

        verticalLayout->addWidget(addBtn);

        editBtn = new QPushButton(layoutWidget);
        editBtn->setObjectName(QStringLiteral("editBtn"));
        editBtn->setEnabled(false);

        verticalLayout->addWidget(editBtn);

        deleteBtn = new QPushButton(layoutWidget);
        deleteBtn->setObjectName(QStringLiteral("deleteBtn"));
        deleteBtn->setEnabled(false);

        verticalLayout->addWidget(deleteBtn);

        configureRelPosBtn = new QPushButton(layoutWidget);
        configureRelPosBtn->setObjectName(QStringLiteral("configureRelPosBtn"));
        configureRelPosBtn->setEnabled(false);

        verticalLayout->addWidget(configureRelPosBtn);

        addToMapBtn = new QPushButton(layoutWidget);
        addToMapBtn->setObjectName(QStringLiteral("addToMapBtn"));
        addToMapBtn->setEnabled(false);

        verticalLayout->addWidget(addToMapBtn);

        pointLightToolBox->addItem(editTool, QStringLiteral("Edit"));
        filterTool = new QWidget();
        filterTool->setObjectName(QStringLiteral("filterTool"));
        filterTool->setGeometry(QRect(0, 0, 121, 147));
        layoutWidget1 = new QWidget(filterTool);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 121, 86));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        nameLbl = new QLabel(layoutWidget1);
        nameLbl->setObjectName(QStringLiteral("nameLbl"));
        nameLbl->setMinimumSize(QSize(47, 0));

        verticalLayout_2->addWidget(nameLbl);

        nameFilterTxt = new QLineEdit(layoutWidget1);
        nameFilterTxt->setObjectName(QStringLiteral("nameFilterTxt"));
        nameFilterTxt->setMinimumSize(QSize(111, 0));

        verticalLayout_2->addWidget(nameFilterTxt);

        sgoNameLbl = new QLabel(layoutWidget1);
        sgoNameLbl->setObjectName(QStringLiteral("sgoNameLbl"));
        sgoNameLbl->setMinimumSize(QSize(61, 0));

        verticalLayout_2->addWidget(sgoNameLbl);

        sgoNameFilterTxt = new QLineEdit(layoutWidget1);
        sgoNameFilterTxt->setObjectName(QStringLiteral("sgoNameFilterTxt"));
        sgoNameFilterTxt->setMinimumSize(QSize(113, 0));

        verticalLayout_2->addWidget(sgoNameFilterTxt);

        pointLightToolBox->addItem(filterTool, QStringLiteral("Filter"));

        retranslateUi(PointLightWidgetToolBox);

        pointLightToolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PointLightWidgetToolBox);
    } // setupUi

    void retranslateUi(QWidget *PointLightWidgetToolBox)
    {
        PointLightWidgetToolBox->setWindowTitle(QApplication::translate("PointLightWidgetToolBox", "PointLightWidgetToolBox", Q_NULLPTR));
        addBtn->setText(QApplication::translate("PointLightWidgetToolBox", "add", Q_NULLPTR));
        editBtn->setText(QApplication::translate("PointLightWidgetToolBox", "edit", Q_NULLPTR));
        deleteBtn->setText(QApplication::translate("PointLightWidgetToolBox", "delete", Q_NULLPTR));
        configureRelPosBtn->setText(QApplication::translate("PointLightWidgetToolBox", "configure rel pos", Q_NULLPTR));
        addToMapBtn->setText(QApplication::translate("PointLightWidgetToolBox", "addToMap", Q_NULLPTR));
        pointLightToolBox->setItemText(pointLightToolBox->indexOf(editTool), QApplication::translate("PointLightWidgetToolBox", "Edit", Q_NULLPTR));
        nameLbl->setText(QApplication::translate("PointLightWidgetToolBox", "name", Q_NULLPTR));
        sgoNameLbl->setText(QApplication::translate("PointLightWidgetToolBox", "sgo name", Q_NULLPTR));
        pointLightToolBox->setItemText(pointLightToolBox->indexOf(filterTool), QApplication::translate("PointLightWidgetToolBox", "Filter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PointLightWidgetToolBox: public Ui_PointLightWidgetToolBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINTLIGHTWIDGETTOOLBOX_H
