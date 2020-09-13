/********************************************************************************
** Form generated from reading UI file 'regform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGFORM_H
#define UI_REGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegForm
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *NameLabel;
    QLineEdit *NameEdit;
    QLabel *PassLabel;
    QLineEdit *PassEdit;
    QLabel *ConPassLabel;
    QLineEdit *ConPassEdit;
    QPushButton *RegBtn;
    QPushButton *AuthBtn;
    QSpacerItem *verticalSpacer_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *RegForm)
    {
        if (RegForm->objectName().isEmpty())
            RegForm->setObjectName(QString::fromUtf8("RegForm"));
        RegForm->resize(691, 478);
        gridLayout = new QGridLayout(RegForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(RegForm);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        splitter->addWidget(verticalLayoutWidget);
        verticalLayoutWidget_2 = new QWidget(splitter);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        NameLabel = new QLabel(verticalLayoutWidget_2);
        NameLabel->setObjectName(QString::fromUtf8("NameLabel"));

        verticalLayout_2->addWidget(NameLabel);

        NameEdit = new QLineEdit(verticalLayoutWidget_2);
        NameEdit->setObjectName(QString::fromUtf8("NameEdit"));

        verticalLayout_2->addWidget(NameEdit);

        PassLabel = new QLabel(verticalLayoutWidget_2);
        PassLabel->setObjectName(QString::fromUtf8("PassLabel"));

        verticalLayout_2->addWidget(PassLabel);

        PassEdit = new QLineEdit(verticalLayoutWidget_2);
        PassEdit->setObjectName(QString::fromUtf8("PassEdit"));

        verticalLayout_2->addWidget(PassEdit);

        ConPassLabel = new QLabel(verticalLayoutWidget_2);
        ConPassLabel->setObjectName(QString::fromUtf8("ConPassLabel"));

        verticalLayout_2->addWidget(ConPassLabel);

        ConPassEdit = new QLineEdit(verticalLayoutWidget_2);
        ConPassEdit->setObjectName(QString::fromUtf8("ConPassEdit"));

        verticalLayout_2->addWidget(ConPassEdit);

        RegBtn = new QPushButton(verticalLayoutWidget_2);
        RegBtn->setObjectName(QString::fromUtf8("RegBtn"));

        verticalLayout_2->addWidget(RegBtn);

        AuthBtn = new QPushButton(verticalLayoutWidget_2);
        AuthBtn->setObjectName(QString::fromUtf8("AuthBtn"));

        verticalLayout_2->addWidget(AuthBtn);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        splitter->addWidget(verticalLayoutWidget_2);
        verticalLayoutWidget_3 = new QWidget(splitter);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_2);

        splitter->addWidget(verticalLayoutWidget_3);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(RegForm);

        QMetaObject::connectSlotsByName(RegForm);
    } // setupUi

    void retranslateUi(QWidget *RegForm)
    {
        RegForm->setWindowTitle(QApplication::translate("RegForm", "Form", nullptr));
        NameLabel->setText(QApplication::translate("RegForm", "<html><head/><body><p><span style=\" font-size:10pt;\">Username:</span></p></body></html>", nullptr));
        PassLabel->setText(QApplication::translate("RegForm", "<html><head/><body><p><span style=\" font-size:10pt;\">Password:</span></p></body></html>", nullptr));
        ConPassLabel->setText(QApplication::translate("RegForm", "<html><head/><body><p><span style=\" font-size:10pt;\">Confirm password:</span></p></body></html>", nullptr));
        RegBtn->setText(QApplication::translate("RegForm", "Registrarion", nullptr));
        AuthBtn->setText(QApplication::translate("RegForm", "Authorized", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegForm: public Ui_RegForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGFORM_H
