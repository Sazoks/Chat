/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QGridLayout *gridLayout;
    QGridLayout *MainLayout;
    QVBoxLayout *verticalLayout;
    QLabel *LabelUsername;
    QPushButton *ProfileBtn;
    QPushButton *MyChanBtn;
    QPushButton *CreateChatBtn;
    QPushButton *ExitBtn;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QGridLayout *Field;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(691, 478);
        gridLayout = new QGridLayout(MainForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        MainLayout = new QGridLayout();
        MainLayout->setObjectName(QString::fromUtf8("MainLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        LabelUsername = new QLabel(MainForm);
        LabelUsername->setObjectName(QString::fromUtf8("LabelUsername"));

        verticalLayout->addWidget(LabelUsername);

        ProfileBtn = new QPushButton(MainForm);
        ProfileBtn->setObjectName(QString::fromUtf8("ProfileBtn"));

        verticalLayout->addWidget(ProfileBtn);

        MyChanBtn = new QPushButton(MainForm);
        MyChanBtn->setObjectName(QString::fromUtf8("MyChanBtn"));

        verticalLayout->addWidget(MyChanBtn);

        CreateChatBtn = new QPushButton(MainForm);
        CreateChatBtn->setObjectName(QString::fromUtf8("CreateChatBtn"));

        verticalLayout->addWidget(CreateChatBtn);

        ExitBtn = new QPushButton(MainForm);
        ExitBtn->setObjectName(QString::fromUtf8("ExitBtn"));

        verticalLayout->addWidget(ExitBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        MainLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        line = new QFrame(MainForm);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        MainLayout->addWidget(line, 0, 1, 1, 1);

        Field = new QGridLayout();
        Field->setObjectName(QString::fromUtf8("Field"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Field->addItem(horizontalSpacer, 0, 0, 1, 1);


        MainLayout->addLayout(Field, 0, 2, 1, 1);

        MainLayout->setColumnStretch(0, 2);
        MainLayout->setColumnStretch(2, 5);

        gridLayout->addLayout(MainLayout, 0, 0, 1, 1);


        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "Form", nullptr));
        LabelUsername->setText(QApplication::translate("MainForm", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
        ProfileBtn->setText(QApplication::translate("MainForm", "Settings", nullptr));
        MyChanBtn->setText(QApplication::translate("MainForm", "My Channel", nullptr));
        CreateChatBtn->setText(QApplication::translate("MainForm", "Channels", nullptr));
        ExitBtn->setText(QApplication::translate("MainForm", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
