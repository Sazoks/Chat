#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include "user.h"
#include "functionalforms.h"
#include <QWidget>
#include <QTcpSocket>
#include <QList>
#include <QByteArray>
#include <QString>

namespace Ui {
class MessageWindow;
}

class MessageWindow : public QWidget
{
    Q_OBJECT
private:
    Ui::MessageWindow *ui;
    FunctionalForms mFunForms;
    QTcpSocket *mTcpSocket;
    User *mUser;

private slots:
    void SendMessage();
    void ReadMessage();

public:
    explicit MessageWindow(User *_user, QWidget *parent = nullptr, QTcpSocket *_socket = nullptr);
    ~MessageWindow();

};

#endif // MESSAGEWINDOW_H
