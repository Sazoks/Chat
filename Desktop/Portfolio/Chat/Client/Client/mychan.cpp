#include "mychan.h"
#include "ui_mychan.h"
#include <QByteArray>
#include <QInputDialog>

MyChan::MyChan(User *_user, QWidget *parent, QTcpSocket *_socket) :
    QWidget(parent),
    ui(new Ui::MyChan)
{
    ui->setupUi(this);
    mUser = _user;
    mTcpSocket = _socket;

    // зависимость GUI от данных
    ChannelWorked = GetStateChannel();
    ui->StateChanBtn->setText((ChannelWorked ? "Stop channel" : "Start channel"));
    Toggled = (ChannelWorked ? true : false);
    ToggleUI();

    connect(ui->ChangeNameBtn, &QPushButton::clicked, this, &MyChan::ChangeName);
    connect(ui->ChangePassBtn, &QPushButton::clicked, this, &MyChan::ChangePassword);
    connect(ui->SetMCUBtn, &QPushButton::clicked, this, &MyChan::SetNewMaxCountUsers);
    connect(ui->ConnectToMyChanBtn, &QPushButton::clicked, this, &MyChan::ConnectToMyChan);
    connect(ui->DeleteMyChanBtn, &QPushButton::clicked, this, &MyChan::DeleteMyChan);
    connect(ui->StateChanBtn, &QPushButton::clicked, this, &MyChan::ChangeStateChan);
}

MyChan::~MyChan()
{
    delete ui;
}

// private
void MyChan::ToggleUI()
{
    if (Toggled) {
        ui->NameChannelLabel->hide();
        ui->NameChannelEdit->hide();
        ui->line->hide();
        ui->OldPassLabel->hide();
        ui->OldPassEdit->hide();
        ui->NewPassLabel->hide();
        ui->NewPassEdit->hide();
        ui->line_2->hide();
        ui->ConNewPassLabel->hide();
        ui->ConNewPassEdit->hide();
        ui->ChangeNameBtn->hide();
        ui->ChangePassBtn->hide();
        ui->MaxCountUsersEdit->hide();
        ui->MaxCountUsersLabel->hide();
        ui->SetMCUBtn->hide();
        ui->ConnectToMyChanBtn->hide();
        Toggled = false;
    }
    else {
        ui->NameChannelLabel->show();
        ui->NameChannelEdit->show();
        ui->line->show();
        ui->OldPassLabel->show();
        ui->OldPassEdit->show();
        ui->NewPassLabel->show();
        ui->NewPassEdit->show();
        ui->line_2->show();
        ui->ConNewPassLabel->show();
        ui->ConNewPassEdit->show();
        ui->ChangeNameBtn->show();
        ui->ChangePassBtn->show();
        ui->MaxCountUsersEdit->show();
        ui->MaxCountUsersLabel->show();
        ui->SetMCUBtn->show();
        ui->ConnectToMyChanBtn->show();
        Toggled = true;
    }
}

bool MyChan::GetStateChannel()
{
    if (!mFunForms.EmitSignalToServer("GetStateChan", mTcpSocket)) {
        mFunForms.ShowMessage("ERROR GET STATE CHANNEL");
        return false;
    }
    mFunForms.SendData(mTcpSocket, "1"); // говорим, что мы готовы принимать данные
    QByteArray Block = mFunForms.GetData(mTcpSocket);
    return (Block == "1" ? true : false);
}

// private slots
void MyChan::ChangeName()
{
    // массив байтов для временно хранения данных
    QByteArray Block;
    QString _nameChannel = ui->NameChannelEdit->text();

    // проверка поля на пустоту
    if (_nameChannel.isEmpty()) {
        mFunForms.ShowMessage("Fill in the field");
        return;
    }

    // сообщаем серверу о нашем желании поменять имея канала
    if (!mFunForms.EmitSignalToServer("ChangeNC", mTcpSocket)) return;

    // отправляем серверу новое имя канала
    mFunForms.SendData(mTcpSocket, _nameChannel.toLocal8Bit());
    Block = mFunForms.GetData(mTcpSocket);
    if (Block == "OK") mFunForms.ShowMessage("The name channel change is successful");
    else mFunForms.ShowMessage("The name channel change is FAILED");
    ui->NameChannelEdit->setText("");
}

void MyChan::ChangePassword()
{
    // массив байтов для временно хранения данных
    QByteArray Block;
    QString _passChannel = ui->OldPassEdit->text();
    QString _newPassChannel = ui->NewPassEdit->text();
    QString _conNewPassChannel = ui->ConNewPassEdit->text();

    // проверка полей
    if (_newPassChannel != _conNewPassChannel) {
        mFunForms.ShowMessage("Password don't mutch");
        return;
    }

    // сообщаем серверу, что хотим изменить пароль для канала
    if (!mFunForms.EmitSignalToServer("ChangePC", mTcpSocket)) return;

    // отсылаю серверу пароли
    Block = (_passChannel + ';' + _newPassChannel).toLocal8Bit();
    mFunForms.SendData(mTcpSocket, Block);

    // получаем ответ от клиента
    Block = mFunForms.GetData(mTcpSocket);
    if (Block == "0") {
        mFunForms.ShowMessage("The password channel change is FAILED");
        return;
    }
    else mFunForms.ShowMessage("The password channel change is successful");
    ui->OldPassEdit->setText("");
    ui->NewPassEdit->setText("");
    ui->ConNewPassEdit->setText("");
}

void MyChan::SetNewMaxCountUsers()
{
    QByteArray Block;
    QString _value = ui->MaxCountUsersEdit->text();

    // проверка на пустоту
    if (_value.isEmpty()) {
        mFunForms.ShowMessage("Fill in the field");
        return;
    }
    // проверка на число
    bool isNumber;
    int _tmp = _value.toInt(&isNumber);
    if (!isNumber) {
        mFunForms.ShowMessage("This is not a number");
        return;
    }
    // проверка на положительность
    if (_tmp <= 0) {
        mFunForms.ShowMessage("The number must be greater than zero");
        return;
    }

    // посылаем серверу сигнал об изменении кол-ва юзеров на канале
    if (!mFunForms.EmitSignalToServer("SetCountU", mTcpSocket)) return;

    // отправляем данные и получаем ответ сервера
    mFunForms.SendData(mTcpSocket, _value.toLocal8Bit());
    Block = mFunForms.GetData(mTcpSocket);
    if (Block != "0") mFunForms.ShowMessage("The max count users on channel change is FAILED");
    else mFunForms.ShowMessage("The max count users on channel change is seccessful");
    ui->MaxCountUsersEdit->setText("");
}

void MyChan::DeleteMyChan()
{
    // сначала остановим канал
    if (ChannelWorked) ChangeStateChan();

    if (!mFunForms.EmitSignalToServer("DeleteChan", mTcpSocket)) return;
    // сообщаем серверу о готовности принятия ответа
    mFunForms.SendData(mTcpSocket, "1");
    // принимаем ответ сервера на запрос
    QByteArray Block = mFunForms.GetData(mTcpSocket);
    if (Block == "0") {
        mFunForms.ShowMessage("Channel deleted");
        mUser->SetAvailChan(false);
        emit SignalDeletedChan();
    }
    else mFunForms.ShowMessage("Channel dont be deleted");
}

void MyChan::ConnectToMyChan()
{
    if (!ChannelWorked) {
        mFunForms.ShowMessage("Channel not worked");
        return;
    }

    // посылаем сигнал серверу о подключении
    if (!mFunForms.EmitSignalToServer("ConnectToChan", mTcpSocket)) {
        mFunForms.ShowMessage("Error connection");
        return;
    }

    // берем имя владельца канала (оно служит нам ID для каналов) и отправляем на сервер
    QByteArray Block = mUser->GetUserName().toLocal8Bit();
    mFunForms.SendData(mTcpSocket, Block);

    // проверка на свободные места и пароля
    if (Block == "0") {
        mFunForms.ShowMessage("Dont free place");
        return;
    }
    if (Block == "1") {
        // запрашиваем пароль
        Block = QInputDialog::getText(this, tr("Enter the password"), tr("Password"), QLineEdit::Normal).toLocal8Bit();
        mFunForms.SendData(mTcpSocket, Block);
        // ждем ответа
        Block = mFunForms.GetData(mTcpSocket);
        if (Block == "2") {
            mFunForms.ShowMessage("Wrong the password");
            return;
        }
    }

    // посылаем сигнал об инициализации окна переписки
    emit SignalInitMsgWindow();
}

void MyChan::ChangeStateChan()
{
    // запрос к серверу об изменении состояния канала
    if (!mFunForms.EmitSignalToServer("ChangeStateChannel", mTcpSocket)) {
        mFunForms.ShowMessage("Error change state channel");
        return;
    }

    // меняем настройки
    if (ChannelWorked) {
        ChannelWorked = false;
        mFunForms.SendData(mTcpSocket, "0");
        ui->StateChanBtn->setText("Start channel");
        mFunForms.ShowMessage("Channel stoped");
    }
    else {
        ChannelWorked = true;
        mFunForms.SendData(mTcpSocket, "1");
        ui->StateChanBtn->setText("Stop channel");
        mFunForms.ShowMessage("Channel started");
    }

    ToggleUI();
}
