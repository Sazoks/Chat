#ifndef USERTHREAD_H
#define USERTHREAD_H

#include "user.h"
#include "channel.h"
#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QMap>
#include <QtSql>
#include <QList>
#include <QMutex>

class Worker : public QObject
{
    Q_OBJECT
private:
    // класс юзера
    User mUser;

    // указатель база данных, дескриптор для сокета, сокет, ID рабоника, кол-во запросов загрузки каналов
    QSqlDatabase *mDatabase;
    QSqlQuery Query;
    qintptr mSockD;
    QTcpSocket *mUserSocket;
    int mID;
    unsigned CountUpload;

    Channel *mMyChan;
    QList<Channel*> &mChannels;
    QMutex *mMutex;

    // асоциативный массив функций
    QMap<QString, void(Worker::*)()> Functions;
    QMap<QString, void(Worker::*)()>::iterator It;

    // служебные фукнции
    void ConnectToDB();
    QByteArray GetData();

    void Registration();
    void Authorized();
    void ChangeName_User();
    void ChangePassword_User();
    void CreateChan();
    void ChangeName_Channel();
    void ChangePassword_Channel();
    void SetNewMaxCountUsers();
    void DeleteCannel();
    void UploadChannels();
    void LogoutOfProfile();
    void ChangeStateChannel();
    void GetStateChan();
    void ConnectToChan();

public slots:
    void StartWork();

signals:
    void StopThread(int);

public:
    Worker(qintptr, int, QSqlDatabase*, QList<Channel*>&, QMutex*);
    ~Worker();
    void printData();
};

#endif // USERTHREAD_H
