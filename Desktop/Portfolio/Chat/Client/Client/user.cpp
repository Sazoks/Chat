#include "user.h"

User::User() {}

void User::SetUsername(QString _Username)
{ mUsername = _Username; }

void User::SetAvailChan(bool _AvailChan)
{ mAvailChan = _AvailChan; }

QString User::GetUserName() const
{ return mUsername; }

bool User::GetAvailChan() const
{ return mAvailChan; }
