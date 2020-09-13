#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QList>
#include <QThread>
#include <QMutex>
#include "worker.h"
#include "channel.h"

class Server : public QTcpServer
{
    Q_OBJECT
private:
    const short MAX_CONNECTION;
    static int CountConnection;

    QMutex mMutex;
    QList<Channel*> mChannels;
    QList<Worker*> Workers;
    QList<QThread*> Threads;
    QSqlDatabase mDatabase;

    // служебные функции
    bool InitActiveChannels();

private slots:
    void ConnectClient();
    void DisconnectClient(int);

public:
    explicit Server(quint16);
    ~Server();
};

#endif // SERVER_H
