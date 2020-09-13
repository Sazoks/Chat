#ifndef USER_H
#define USER_H

#include <QString>
#include <QDebug>

class User
{
private:
    bool mAvailChan;
    QString mUsername;

public:
    User();
    void PrintDataUser() const;

    void SetUsername(QString);
    void SetAvailChan(bool);

    QString GetUserName() const;
    bool GetAvailChan() const;
};

#endif // USER_H
