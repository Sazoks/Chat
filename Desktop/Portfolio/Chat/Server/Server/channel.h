#ifndef CHANNEL_H
#define CHANNEL_H

#include "user.h"
#include <QString>
#include <QList>
#include <QTcpSocket>

class Channel
{
private:
    // подключенные к каналу
    QList<User*> mConnectionUsers;
    QString mName, mPassword, mOwner;
    int mMaxCountUsers, mCurrentCountUsers;

    // служебный функции
    void PrintInfoConnections();

public:
    Channel(const QString &_name = "", const QString &_password = "", const QString &_owner = "", int _maxCountUsers = 0);

    QString GetOwner() const;
    bool AvailFreePlace() const;
    bool AvailPassword() const;
    void AddUser(User*);
    bool CheckPassword(const QString&) const;
    void SendMsgToUsers(const QString&, const QString&);
    void DeleteUser(const QString&);

    /*void SetMaxCountUsers(int);
    void SetNameChannel(QString);
    void SetPasswordChannel(QString);*/
};

#endif // CHANNEL_H
