#include "regform.h"
#include "ui_regform.h"
#include <QPushButton>
#include <QDebug>

RegForm::RegForm(User *_user, QWidget *parent, QTcpSocket *_Socket) :
    QWidget(parent),
    ui(new Ui::RegForm)
{
    ui->setupUi(this);
    connect(ui->AuthBtn, &QPushButton::clicked, this, &RegForm::SlotAuthBtn);
    connect(ui->RegBtn, &QPushButton::clicked, this, &RegForm::SlotRegBtn);

    mTcpSocket = _Socket;
    mUser = _user;
}

RegForm::~RegForm()
{
    delete ui;
}

void RegForm::SlotRegBtn()
{
    QString _nameEdit = ui->NameEdit->text();
    QString _passEdit = ui->PassEdit->text();
    QString _conPassEdit = ui->ConPassEdit->text();

    // проверка данных
    if (_nameEdit.isEmpty() || _passEdit.isEmpty() || _conPassEdit.isEmpty()) {
        mFunForms.ShowMessage("FILL IN ALL FIELDS");
        return;
    }
    if (_passEdit != _conPassEdit) {
        mFunForms.ShowMessage("PASSWORDS DON'T MATCH");
        return;
    }

    //  сообщаем серверу, что хотим зарегистрироваться
    mFunForms.EmitSignalToServer("Reg", mTcpSocket);

    // отправляем данные на сервер
    QByteArray Block = _nameEdit.toLocal8Bit() + ";" + _passEdit.toLocal8Bit();
    mFunForms.SendData(mTcpSocket, Block);

    // здесь будет проверка на валидность
    Block = mFunForms.GetData(mTcpSocket);
    if (Block != "0") {
        mFunForms.ShowMessage(Block);
        return;
    }

    // сохраняем имя юзера
    mUser->SetUsername(_nameEdit);
    mUser->SetAvailChan(false);
    emit SignalRegBtn("RegForm_1");
}

void RegForm::SlotAuthBtn()
{
    emit SignalAuthBtn("RegForm_2");
}
