#ifndef AUTHFORM_H
#define AUTHFORM_H

#include "user.h"
#include "functionalforms.h"
#include <QWidget>
#include <QString>
#include <QByteArray>
#include <QTcpSocket>

namespace Ui {
class AuthForm;
}

class AuthForm : public QWidget
{
    Q_OBJECT
private:
    FunctionalForms mFunForms;
    Ui::AuthForm *ui;
    QTcpSocket *mTcpSocket;
    User *mUser;

public:
    explicit AuthForm(User *_user, QWidget *parent = nullptr, QTcpSocket* _Socket = nullptr);
    ~AuthForm();

private slots:
    void SlotAuthBtn();
    void SlotRegBtn();

signals:
    void SignalAuthBtn(QString);
    void SignalRegBtn(QString);

};

#endif // AUTHFORM_H
