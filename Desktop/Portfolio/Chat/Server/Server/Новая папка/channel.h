#ifndef CHANNEL_H
#define CHANNEL_H

#include <QString>
#include <QList>
#include <QTcpSocket>

class Channel
{
private:
    // подключенные к каналу
    QList<QTcpSocket*> mTcpUsersSockets;
    QString mName, mPassword, mOwner;
    int mMaxCountUsers, mCurrentCountUsers;

public:
    Channel(const QString &_name = "", const QString &_password = "", const QString &_owner = "", int _maxCountUsers = 0);

    void PrintData() const;
    QString GetOwner() const;
};

#endif // CHANNEL_H
