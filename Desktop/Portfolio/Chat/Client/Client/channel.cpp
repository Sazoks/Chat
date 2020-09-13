#include "channel.h"
#include <QDebug>

Channel::Channel(const QList<QByteArray> &_chanParams)
    : Name(_chanParams[0]),
      MaxUsers(_chanParams[1]),
      Owner(_chanParams[2]),
      Avpass(_chanParams[3]) {}

QString Channel::GetName() const
{ return Name; }
QString Channel::GetMaxUsers() const
{ return MaxUsers; }
QString Channel::GetOwner() const
{ return Owner; }
QString Channel::GetAvpass() const
{ return Avpass; }

void Channel::PrintData() const
{
    qDebug() << "Name: " << Name<< '\n'
             << "MaxUsers: " << MaxUsers << '\n'
             << "Owner: " << Owner << '\n'
             << "Avail pass: " << Avpass << '\n';
}
