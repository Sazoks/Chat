#ifndef USER_H
#define USER_H

#include <QString>
#include <QDebug>
#include <QTcpSocket>

class Channel;

class User : public QObject
{
    Q_OBJECT
private:
    bool mAvailChan;
    QString mUsername;
    QTcpSocket *mTcpSocket;
    int mCountUpload,
        mId;
    Channel *mCurrentChannel;

signals:
    void SignalMyDisconnect(int);
    void SignalMyReadyRead();

private slots:
    void SlotMyDisconnect();
    void SlotMyReadyRead();

public:
    User(QTcpSocket *_socket, int _id = -1, QObject *parent = nullptr);
    ~User();

    // сеттеры
    void SetTcpSocket(QTcpSocket*);
    void SetUsername(QString);
    void SetAvailChan(bool);
    void SetCountUpload(int);
    void SetCurrentChannel(Channel*);

    // геттеры
    QTcpSocket* GetTcpSocket();
    Channel* GetCurrentChannel();
    QString GetUserName() const;
    bool GetAvailChan() const;
    int GetCountUpload() const;
};

#endif // USER_H
