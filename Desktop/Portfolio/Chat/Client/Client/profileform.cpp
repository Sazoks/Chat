#include "profileform.h"
#include "ui_profileform.h"

ProfileForm::ProfileForm(User *_user, QWidget *parent, QTcpSocket *_sock) :
    QWidget(parent),
    ui(new Ui::ProfileForm)
{
    ui->setupUi(this);
    mTcpSocket = _sock;
    mUser = _user;

    // connect'ы
    QObject::connect(ui->ChangeUsername, &QPushButton::clicked, this, &ProfileForm::SlotChangeUsername);
    QObject::connect(ui->ChangePass, &QPushButton::clicked, this, &ProfileForm::SlotChangePassword);
}

ProfileForm::~ProfileForm()
{
    delete ui;
}


// slots
void ProfileForm::SlotChangeUsername()
{
    // массив байтов для временно хранения данных
    QByteArray Block;

    // проверка поля на пустоту
    if (ui->UsernameEdit->text().isEmpty()) {
        mFunForms.ShowMessage("Fill in the field");
        return;
    }

    // посылаем сигнал серверу, что хотим поменять имя
    mFunForms.EmitSignalToServer("ChangeNU", mTcpSocket);

    // посылаем серверу имя, на которое хотим заменить текущее
    Block = ui->UsernameEdit->text().toLocal8Bit();
    mFunForms.SendData(mTcpSocket, Block);

    // получаем ответ сервера
    Block = mFunForms.GetData(mTcpSocket);
    if (Block == "1") {
        mUser->SetUsername(ui->UsernameEdit->text());
        mFunForms.ShowMessage("The username change is successful");
    }
    else mFunForms.ShowMessage("USERNAME IS BUSY");
    ui->UsernameEdit->setText("");

    emit SignalChangeUsername();
}


void ProfileForm::SlotChangePassword()
{
    // массив байтов для временно хранения данных
    QByteArray Block;
    QByteArray _oldPass = ui->OldPassEdit->text().toLocal8Bit();
    QByteArray _newPass = ui->NewPassEdit->text().toLocal8Bit();
    QByteArray _conNewPass = ui->ConNewPassEdit->text().toLocal8Bit();

    // проверка полей
    if (_oldPass.isEmpty() || _newPass.isEmpty() || _conNewPass.isEmpty()) {
        mFunForms.ShowMessage("Fill all fields");
        return;
    }
    if (_newPass != _conNewPass) {
        mFunForms.ShowMessage("Passwords dong's match");
        return;
    }

    // сообщаем серверу, что хотим изменить пароль
    mFunForms.EmitSignalToServer("ChangePU", mTcpSocket);

    // посылаем серверу данные
    Block = _oldPass + ";" + _newPass;
    mFunForms.SendData(mTcpSocket, Block);

    // ждем ответа
    Block = mFunForms.GetData(mTcpSocket);
    if (Block != "1") mFunForms.ShowMessage(Block);
    else mFunForms.ShowMessage("The password change is successful");
    ui->OldPassEdit->setText("");
    ui->NewPassEdit->setText("");
    ui->ConNewPassEdit->setText("");
}
