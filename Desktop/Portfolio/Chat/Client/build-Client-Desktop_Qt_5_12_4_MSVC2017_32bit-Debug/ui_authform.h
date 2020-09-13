/********************************************************************************
** Form generated from reading UI file 'authform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHFORM_H
#define UI_AUTHFORM_H

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

class Ui_AuthForm
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
    QPushButton *AuthBtn;
    QPushButton *RegBtn;
    QSpacerItem *verticalSpacer_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *AuthForm)
    {
        if (AuthForm->objectName().isEmpty())
            AuthForm->setObjectName(QString::fromUtf8("AuthForm"));
        AuthForm->resize(691, 478);
        gridLayout = new QGridLayout(AuthForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(AuthForm);
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

        AuthBtn = new QPushButton(verticalLayoutWidget_2);
        AuthBtn->setObjectName(QString::fromUtf8("AuthBtn"));

        verticalLayout_2->addWidget(AuthBtn);

        RegBtn = new QPushButton(verticalLayoutWidget_2);
        RegBtn->setObjectName(QString::fromUtf8("RegBtn"));

        verticalLayout_2->addWidget(RegBtn);

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


        retranslateUi(AuthForm);

        QMetaObject::connectSlotsByName(AuthForm);
    } // setupUi

    void retranslateUi(QWidget *AuthForm)
    {
        AuthForm->setWindowTitle(QApplication::translate("AuthForm", "Form", nullptr));
        NameLabel->setText(QApplication::translate("AuthForm", "<html><head/><body><p><span style=\" font-size:10pt;\">Username:</span></p></body></html>", nullptr));
        PassLabel->setText(QApplication::translate("AuthForm", "<html><head/><body><p><span style=\" font-size:10pt;\">Password:</span></p></body></html>", nullptr));
        AuthBtn->setText(QApplication::translate("AuthForm", "Authorized", nullptr));
        RegBtn->setText(QApplication::translate("AuthForm", "Registrarion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthForm: public Ui_AuthForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHFORM_H
