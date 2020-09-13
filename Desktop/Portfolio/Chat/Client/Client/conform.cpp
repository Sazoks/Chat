#include "conform.h"
#include "ui_conform.h"
#include <QPushButton>

ConForm::ConForm(QWidget *parent, QTcpSocket* _socket) :
    QWidget(parent),
    ui(new Ui::ConForm)
{
    ui->setupUi(this);
    mTcpSocket = _socket;
    connect(ui->ConnectBtn, &QPushButton::clicked, this, &ConForm::SlotConnectBtn);
}

ConForm::~ConForm()
{
    delete ui;
}

void ConForm::SlotConnectBtn()
{
    QString _addr = ui->AddrEdit->text();
    QString _port = ui->PortEdit->text();

    if (_addr.isEmpty() || _port.isEmpty()) {
        mFunForms.ShowMessage("Fill all fields");
        return;
    }

    // это неблокирующий вызов
    mTcpSocket->connectToHost(_addr, _port.toUShort());
    // мы должны подождать
    if(!mTcpSocket->waitForConnected(5000))
    {
        mFunForms.ShowMessage("Error: " + mTcpSocket->errorString());
        return;
    }

    QByteArray Block = mFunForms.GetData(mTcpSocket);

    emit SignalConnectBtn("ConForm");
}
