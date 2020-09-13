#include "user.h"

User::User(QTcpSocket *_socket, int _id, QObject *parent)
    : QObject(parent),
      mTcpSocket(_socket),
      mCountUpload(0),
      mId(_id),
      mCurrentChannel(nullptr)
{
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &User::SlotMyDisconnect);
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &User::SlotMyReadyRead);
}

User::~User()
{
    mTcpSocket->close();
    delete mTcpSocket;
}


// private slots
void User::SlotMyDisconnect()
{
    emit SignalMyDisconnect(mId);
}

void User::SlotMyReadyRead()
{
    emit SignalMyReadyRead();
}


// геттеры и сеттеры
void User::SetUsername(QString _Username)
{ mUsername = _Username; }

void User::SetAvailChan(bool _AvailChan)
{ mAvailChan = _AvailChan; }

void User::SetTcpSocket(QTcpSocket* _socket)
{ mTcpSocket = _socket; }

void User::SetCountUpload(int _countUpload)
{ mCountUpload = _countUpload; }

void User::SetCurrentChannel(Channel* _channel)
{ mCurrentChannel = _channel; }


QTcpSocket* User::GetTcpSocket()
{ return mTcpSocket; }

QString User::GetUserName() const
{ return mUsername; }

bool User::GetAvailChan() const
{ return mAvailChan; }

int User::GetCountUpload() const
{ return mCountUpload; }

Channel* User::GetCurrentChannel()
{ return mCurrentChannel; }
