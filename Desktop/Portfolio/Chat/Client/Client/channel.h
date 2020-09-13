#ifndef CHANNEL_H
#define CHANNEL_H

#include <QList>
#include <QByteArray>
#include <QString>

class Channel
{
private:
    QString Name, MaxUsers, Owner, Avpass;
public:
    Channel(const QList<QByteArray>&);
    QString GetName() const;
    QString GetMaxUsers() const;
    QString GetOwner() const;
    QString GetAvpass() const;
    void PrintData() const;
};

#endif // CHANNEL_H
