#include "client.h"
#include <QByteArray>

Client::Client()
{
    mAuthForm = nullptr;
    mRegForm = nullptr;
    mMainForm = nullptr;

    mTcpSocket = new QTcpSocket;
    mConnectForm = new ConForm(this, mTcpSocket);
    connect(mConnectForm, &ConForm::SignalConnectBtn, this, &Client::ChangedWidget);
    setCentralWidget(mConnectForm);
}

Client::~Client()
{
    mTcpSocket->disconnectFromHost();
    DeleteCurrentWidget();
    delete mTcpSocket;
}

void Client::DeleteCurrentWidget()
{
    if (mAuthForm) {
        delete mAuthForm;
        mAuthForm = nullptr;
    }
    if (mRegForm) {
        delete mRegForm;
        mRegForm = nullptr;
    }
    if (mMainForm) {
        delete mMainForm;
        mMainForm = nullptr;
    }
    if (mConnectForm) {
        delete mConnectForm;
        mConnectForm = nullptr;
    }
}

void Client::InitAuthForm()
{
    mAuthForm = new AuthForm(&mUser, this, mTcpSocket);
    connect(mAuthForm, &AuthForm::SignalAuthBtn, this, &Client::ChangedWidget);
    connect(mAuthForm, &AuthForm::SignalRegBtn, this, &Client::ChangedWidget);
    setCentralWidget(mAuthForm);
}

void Client::InitRegForm()
{
    mRegForm = new RegForm(&mUser, this, mTcpSocket);
    connect(mRegForm, &RegForm::SignalAuthBtn, this, &Client::ChangedWidget);
    connect(mRegForm, &RegForm::SignalRegBtn, this, &Client::ChangedWidget);
    setCentralWidget(mRegForm);
}

void Client::InitMainForm()
{
    mMainForm = new MainForm(&mUser, this, mTcpSocket);
    connect(mMainForm, &MainForm::SignalExit, this, &Client::ChangedWidget);
    setCentralWidget(mMainForm);
}

void Client::ChangedWidget(QString _sender)
{
    DeleteCurrentWidget();

    if (_sender == "ConForm" || _sender == "RegForm_2" || _sender == "Exit") InitAuthForm(); // клиент подключился к серверу
    else if (_sender == "AuthForm_1" || _sender == "RegForm_1") InitMainForm(); // клиент вошел изи зареглася
    else if (_sender == "AuthForm_2") InitRegForm(); // клиент хочет зарегаться
}
