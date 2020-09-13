#ifndef SERVER_H
#define SERVER_H

#include "user.h"
#include "channel.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QList>
#include <QtSql>
#include <QThread>

class Server : public QTcpServer
{
    Q_OBJECT
private:
    const short MAX_CONNECTION;
    static int CountConnection;

    QList<Channel*> mChannels;
    QList<User*> mUsers;
    QSqlDatabase mDatabase;

    // асоциативный массив функций
    QMap<QString, void(Server::*)(User*)> Functions;
    QMap<QString, void(Server::*)(User*)>::iterator It;

    // служебные функции
    bool InitActiveChannels();
    void InitCommandsList();
    void ConnectToDB(User*);
    QByteArray GetData(User*);
    void SendData(User*, const QByteArray&);

    void Registration(User*);
    void Authorized(User*);
    void ChangeName_User(User*);
    void ChangePassword_User(User*);
    void CreateChan(User*);
    void ChangeName_Channel(User*);
    void ChangePassword_Channel(User*);
    void SetNewMaxCountUsers(User*);
    void DeleteCannel(User*);
    void UploadChannels(User*);
    void LogoutOfProfile(User*);
    void ChangeStateChannel(User*);
    void GetStateChan(User*);
    void ConnectToChan(User*);
    void DisconnectChan(User*);

private slots:
    void ConnectClient();
    void DisconnectClient(int);
    void CommandHandler();

public:
    explicit Server(quint16);
    ~Server();
};

#endif // SERVER_H
