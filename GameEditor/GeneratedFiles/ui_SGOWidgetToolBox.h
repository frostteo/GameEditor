/********************************************************************************
** Form generated from reading UI file 'SGOWidgetToolBox.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SGOWIDGETTOOLBOX_H
#define UI_SGOWIDGETTOOLBOX_H

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

class Ui_SGOWidgetToolBox
{
public:
    QVBoxLayout *verticalLayout_2;
    QToolBox *SGOToolBox;
    QWidget *EditSGOTool;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *addSGOBtn;
    QPushButton *editSGOBtn;
    QPushButton *deleteSGOBtn;
    QPushButton *previewSGOBtn;
    QWidget *SGOFilterTool;
    QLabel *nameLbl;
    QLineEdit *SGONameFilterTxt;
    QLabel *modelLbl;
    QLineEdit *SGOModelFilterTxt;

    void setupUi(QWidget *SGOWidgetToolBox)
    {
        if (SGOWidgetToolBox->objectName().isEmpty())
            SGOWidgetToolBox->setObjectName(QStringLiteral("SGOWidgetToolBox"));
        SGOWidgetToolBox->resize(150, 190);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SGOWidgetToolBox->sizePolicy().hasHeightForWidth());
        SGOWidgetToolBox->setSizePolicy(sizePolicy);
        SGOWidgetToolBox->setMinimumSize(QSize(150, 190));
        verticalLayout_2 = new QVBoxLayout(SGOWidgetToolBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        SGOToolBox = new QToolBox(SGOWidgetToolBox);
        SGOToolBox->setObjectName(QStringLiteral("SGOToolBox"));
        EditSGOTool = new QWidget();
        EditSGOTool->setObjectName(QStringLiteral("EditSGOTool"));
        EditSGOTool->setGeometry(QRect(0, 0, 132, 118));
        layoutWidget = new QWidget(EditSGOTool);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 0, 77, 112));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        addSGOBtn = new QPushButton(layoutWidget);
        addSGOBtn->setObjectName(QStringLiteral("addSGOBtn"));

        verticalLayout->addWidget(addSGOBtn);

        editSGOBtn = new QPushButton(layoutWidget);
        editSGOBtn->setObjectName(QStringLiteral("editSGOBtn"));
        editSGOBtn->setEnabled(false);

        verticalLayout->addWidget(editSGOBtn);

        deleteSGOBtn = new QPushButton(layoutWidget);
        deleteSGOBtn->setObjectName(QStringLiteral("deleteSGOBtn"));
        deleteSGOBtn->setEnabled(false);

        verticalLayout->addWidget(deleteSGOBtn);

        previewSGOBtn = new QPushButton(layoutWidget);
        previewSGOBtn->setObjectName(QStringLiteral("previewSGOBtn"));
        previewSGOBtn->setEnabled(false);

        verticalLayout->addWidget(previewSGOBtn);

        SGOToolBox->addItem(EditSGOTool, QStringLiteral("Edit"));
        SGOFilterTool = new QWidget();
        SGOFilterTool->setObjectName(QStringLiteral("SGOFilterTool"));
        SGOFilterTool->setGeometry(QRect(0, 0, 132, 118));
        nameLbl = new QLabel(SGOFilterTool);
        nameLbl->setObjectName(QStringLiteral("nameLbl"));
        nameLbl->setGeometry(QRect(1, 1, 26, 16));
        SGONameFilterTxt = new QLineEdit(SGOFilterTool);
        SGONameFilterTxt->setObjectName(QStringLiteral("SGONameFilterTxt"));
        SGONameFilterTxt->setGeometry(QRect(1, 20, 121, 20));
        modelLbl = new QLabel(SGOFilterTool);
        modelLbl->setObjectName(QStringLiteral("modelLbl"));
        modelLbl->setGeometry(QRect(1, 46, 28, 16));
        SGOModelFilterTxt = new QLineEdit(SGOFilterTool);
        SGOModelFilterTxt->setObjectName(QStringLiteral("SGOModelFilterTxt"));
        SGOModelFilterTxt->setGeometry(QRect(1, 65, 121, 20));
        SGOToolBox->addItem(SGOFilterTool, QStringLiteral("Filter"));
        nameLbl->raise();
        SGONameFilterTxt->raise();
        modelLbl->raise();
        SGOModelFilterTxt->raise();

        verticalLayout_2->addWidget(SGOToolBox);


        retranslateUi(SGOWidgetToolBox);

        SGOToolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SGOWidgetToolBox);
    } // setupUi

    void retranslateUi(QWidget *SGOWidgetToolBox)
    {
        SGOWidgetToolBox->setWindowTitle(QApplication::translate("SGOWidgetToolBox", "SGOWidgetToolBox", Q_NULLPTR));
        addSGOBtn->setText(QApplication::translate("SGOWidgetToolBox", "add", Q_NULLPTR));
        editSGOBtn->setText(QApplication::translate("SGOWidgetToolBox", "edit", Q_NULLPTR));
        deleteSGOBtn->setText(QApplication::translate("SGOWidgetToolBox", "delete", Q_NULLPTR));
        previewSGOBtn->setText(QApplication::translate("SGOWidgetToolBox", "preview", Q_NULLPTR));
        SGOToolBox->setItemText(SGOToolBox->indexOf(EditSGOTool), QApplication::translate("SGOWidgetToolBox", "Edit", Q_NULLPTR));
        nameLbl->setText(QApplication::translate("SGOWidgetToolBox", "name", Q_NULLPTR));
        modelLbl->setText(QApplication::translate("SGOWidgetToolBox", "model", Q_NULLPTR));
        SGOToolBox->setItemText(SGOToolBox->indexOf(SGOFilterTool), QApplication::translate("SGOWidgetToolBox", "Filter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SGOWidgetToolBox: public Ui_SGOWidgetToolBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SGOWIDGETTOOLBOX_H
