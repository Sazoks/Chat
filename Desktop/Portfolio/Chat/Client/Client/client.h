#ifndef CLIENT_H
#define CLIENT_H

#include "user.h"
#include "conform.h"
#include "regform.h"
#include "authform.h"
#include "mainform.h"

#include <QMainWindow>
#include <QString>
#include <QTcpSocket>

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT
private:
    ConForm *mConnectForm;
    RegForm *mRegForm;
    AuthForm *mAuthForm;
    MainForm *mMainForm;

    void InitAuthForm();
    void InitRegForm();
    void InitMainForm();
    void DeleteCurrentWidget();

    QTcpSocket *mTcpSocket;
    User mUser;

private slots:
    void ChangedWidget(QString _sender);

signals:

public:
    Client();
    ~Client();
};

#endif // CLIENT_H
