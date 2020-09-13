#ifndef PROFILEFORM_H
#define PROFILEFORM_H

#include "user.h"
#include "functionalforms.h"
#include <QWidget>
#include <QPushButton>
#include <QTcpSocket>
#include <QByteArray>

namespace Ui {
class ProfileForm;
}

class ProfileForm : public QWidget
{
    Q_OBJECT
private:
    FunctionalForms mFunForms;
    Ui::ProfileForm *ui;
    QTcpSocket *mTcpSocket;
    User *mUser;

private slots:
    void SlotChangeUsername();
    void SlotChangePassword();

signals:
    void SignalChangeUsername();

public:
    explicit ProfileForm(User *_user, QWidget *parent = nullptr, QTcpSocket *_sock = nullptr);
    ~ProfileForm();

};

#endif // PROFILEFORM_H
