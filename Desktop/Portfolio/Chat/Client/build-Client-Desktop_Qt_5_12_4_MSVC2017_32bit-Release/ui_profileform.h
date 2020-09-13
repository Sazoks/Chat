/********************************************************************************
** Form generated from reading UI file 'profileform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILEFORM_H
#define UI_PROFILEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProfileForm
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QPushButton *ChangePass;
    QLineEdit *ConNewPassEdit;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *OldPassEdit;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *ChangeUsername;
    QLineEdit *UsernameEdit;
    QLabel *label_5;
    QLineEdit *NewPassEdit;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ProfileForm)
    {
        if (ProfileForm->objectName().isEmpty())
            ProfileForm->setObjectName(QString::fromUtf8("ProfileForm"));
        ProfileForm->resize(691, 478);
        gridLayout_2 = new QGridLayout(ProfileForm);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, -1, -1, -1);
        label = new QLabel(ProfileForm);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 16, 1, 1, 1);

        ChangePass = new QPushButton(ProfileForm);
        ChangePass->setObjectName(QString::fromUtf8("ChangePass"));

        gridLayout->addWidget(ChangePass, 12, 1, 1, 1);

        ConNewPassEdit = new QLineEdit(ProfileForm);
        ConNewPassEdit->setObjectName(QString::fromUtf8("ConNewPassEdit"));

        gridLayout->addWidget(ConNewPassEdit, 11, 1, 1, 1);

        label_4 = new QLabel(ProfileForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 10, 1, 1, 1);

        label_3 = new QLabel(ProfileForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 5, 1, 1, 1);

        label_2 = new QLabel(ProfileForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        OldPassEdit = new QLineEdit(ProfileForm);
        OldPassEdit->setObjectName(QString::fromUtf8("OldPassEdit"));

        gridLayout->addWidget(OldPassEdit, 6, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 5, 2, 1, 1);

        ChangeUsername = new QPushButton(ProfileForm);
        ChangeUsername->setObjectName(QString::fromUtf8("ChangeUsername"));

        gridLayout->addWidget(ChangeUsername, 3, 1, 1, 1);

        UsernameEdit = new QLineEdit(ProfileForm);
        UsernameEdit->setObjectName(QString::fromUtf8("UsernameEdit"));

        gridLayout->addWidget(UsernameEdit, 2, 1, 1, 1);

        label_5 = new QLabel(ProfileForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 7, 1, 1, 1);

        NewPassEdit = new QLineEdit(ProfileForm);
        NewPassEdit->setObjectName(QString::fromUtf8("NewPassEdit"));

        gridLayout->addWidget(NewPassEdit, 8, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 5, 0, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 5);
        gridLayout->setColumnStretch(2, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(ProfileForm);

        QMetaObject::connectSlotsByName(ProfileForm);
    } // setupUi

    void retranslateUi(QWidget *ProfileForm)
    {
        ProfileForm->setWindowTitle(QApplication::translate("ProfileForm", "Form", nullptr));
        label->setText(QApplication::translate("ProfileForm", "<html><head/><body><p align=\"center\"><br/></p><p align=\"center\"><span style=\" font-size:14pt;\">Profile settings</span></p><p align=\"center\"><br/></p></body></html>", nullptr));
        ChangePass->setText(QApplication::translate("ProfileForm", "Change", nullptr));
        label_4->setText(QApplication::translate("ProfileForm", "Confirm new password:", nullptr));
        label_3->setText(QApplication::translate("ProfileForm", "Old password:", nullptr));
        label_2->setText(QApplication::translate("ProfileForm", "Username:", nullptr));
        ChangeUsername->setText(QApplication::translate("ProfileForm", "Change", nullptr));
        label_5->setText(QApplication::translate("ProfileForm", "New password:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProfileForm: public Ui_ProfileForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILEFORM_H
