#include "channel.h"

Channel::Channel(const QString &_name, const QString &_password, const QString &_owner, int _maxCountUsers)
    : mName(_name),
      mPassword(_password),
      mOwner(_owner),
      mMaxCountUsers(_maxCountUsers),
      mCurrentCountUsers(0)
{

}

void Channel::PrintData() const
{
    qDebug() << "Name: " << mName << '\n'
             << "Pass: " << mPassword << '\n'
             << "Owner: " << mOwner << '\n'
             << "Max count users: " << mMaxCountUsers << '\n';
}

QString Channel::GetOwner() const
{ return mOwner; }
