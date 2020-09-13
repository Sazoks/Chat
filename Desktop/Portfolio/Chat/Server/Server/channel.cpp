#include "channel.h"

Channel::Channel(const QString &_name, const QString &_password, const QString &_owner, int _maxCountUsers)
    : mName(_name),
      mPassword(_password),
      mOwner(_owner),
      mMaxCountUsers(_maxCountUsers),
      mCurrentCountUsers(0)
{
    // инициализируем массив указателей nullptr
    mConnectionUsers.reserve(mMaxCountUsers);
    for (int i = 0; i < mMaxCountUsers; i++)
        mConnectionUsers.append(nullptr);
}


QString Channel::GetOwner() const
{ return mOwner; }

bool Channel::AvailFreePlace() const
{ return (mCurrentCountUsers < mMaxCountUsers ? true : false); }

bool Channel::AvailPassword() const
{ return (mPassword == "" ? false : true); }

bool Channel::CheckPassword(const QString &_password) const
{ return (_password == mPassword ? true : false); }


void Channel::AddUser(User *newUser)
{
    // поиск свободного места
    int IndFreePlace = -1;
    for (int i = 0; i < mMaxCountUsers; i++)
        if (!mConnectionUsers[i]) {
            IndFreePlace = i;
            break;
        }

    // добавляем
    if (IndFreePlace != -1)
        mConnectionUsers[IndFreePlace] = newUser;

    qDebug() << mConnectionUsers[IndFreePlace]->GetUserName() << " connected to " << mOwner + "@" + mName;
    PrintInfoConnections();
}

void Channel::DeleteUser(const QString &owner)
{
    for (int i = 0; i < mMaxCountUsers; i++)
        if (mConnectionUsers[i])
            if (mConnectionUsers[i]->GetUserName() == owner) {
                qDebug() << mConnectionUsers[i]->GetUserName() << " disconnected from " << mOwner + "@" + mName;
                mConnectionUsers[i] = nullptr;
                break;
        }
    PrintInfoConnections();
}


void Channel::SendMsgToUsers(const QString &msg, const QString &sender)
{
    for (int i = 0; i < mMaxCountUsers; i++)
        if (mConnectionUsers[i])
            mConnectionUsers[i]->GetTcpSocket()->write((sender + ": " + msg).toLocal8Bit());
}

// private
void Channel::PrintInfoConnections()
{
    for (int i = 0; i < mMaxCountUsers; i++)
        if (mConnectionUsers[i]) qDebug() << "work" << i;
        else qDebug() << "dont work" << i;
}
