#ifndef MYCHAN_H
#define MYCHAN_H

#include "user.h"
#include "functionalforms.h"
#include <QWidget>
#include <QPushButton>
#include <QTcpSocket>
#include <QString>

namespace Ui {
class MyChan;
}

class MyChan : public QWidget
{
    Q_OBJECT

private:
    FunctionalForms mFunForms;
    Ui::MyChan *ui;
    QTcpSocket *mTcpSocket;
    User *mUser;
    bool ChannelWorked, Toggled;

    // служебные функции
    bool GetStateChannel();
    void ToggleUI();

private slots:
    void ChangeName();
    void ChangePassword();
    void SetNewMaxCountUsers();
    void ConnectToMyChan();
    void DeleteMyChan();
    void ChangeStateChan();

signals:
    void SignalDeletedChan();
    void SignalInitMsgWindow();

public:
    explicit MyChan(User *_user = nullptr, QWidget *parent = nullptr, QTcpSocket *_socket = nullptr);
    ~MyChan();
    //void SetDefaultSettings();
};

#endif // MYCHAN_H
