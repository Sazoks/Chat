#include "authform.h"
#include "ui_authform.h"
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

AuthForm::AuthForm(User *_user, QWidget *parent, QTcpSocket *_Socket) :
    QWidget(parent),
    ui(new Ui::AuthForm)
{
    ui->setupUi(this);
    connect(ui->AuthBtn, &QPushButton::clicked, this, &AuthForm::SlotAuthBtn);
    connect(ui->RegBtn, &QPushButton::clicked, this, &AuthForm::SlotRegBtn);

    mTcpSocket = _Socket;
    mUser = _user;
}

AuthForm::~AuthForm()
{
    delete ui;
}

void AuthForm::SlotAuthBtn()
{
    // проверка данных
    if (ui->NameEdit->text().isEmpty() || ui->PassEdit->text().isEmpty()) {
        mFunForms.ShowMessage("FILL IN ALL FIELDS");
        return;
    }

    //  сообщаем серверу, что хотим авторизироваться
    if (!mFunForms.EmitSignalToServer("Auth", mTcpSocket)) return;

    // отправляем данные на сервер
    QByteArray Block = (ui->NameEdit->text() + ";" + ui->PassEdit->text()).toLocal8Bit();
    mFunForms.SendData(mTcpSocket, Block);

    // здесь будет проверка на валидность
    Block = mFunForms.GetData(mTcpSocket);
    if (Block == "ERROR AUTHORIZED") {
        mFunForms.ShowMessage(Block);
        return;
    }

    // сохраняем имя юзера и состояние наличия канала
    mUser->SetUsername(ui->NameEdit->text());
    mUser->SetAvailChan((Block == "1" ? true : false));
    emit SignalAuthBtn("AuthForm_1");
}

void AuthForm::SlotRegBtn()
{
    emit SignalRegBtn("AuthForm_2");
}
