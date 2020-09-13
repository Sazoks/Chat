#ifndef REGFORM_H
#define REGFORM_H

#include "user.h"
#include "functionalforms.h"
#include <QWidget>
#include <QString>
#include <QByteArray>
#include <QTcpSocket>

namespace Ui {
class RegForm;
}

class RegForm : public QWidget
{
    Q_OBJECT

private:
    FunctionalForms mFunForms;
    Ui::RegForm *ui;
    QTcpSocket *mTcpSocket;
    User *mUser;

public:
    explicit RegForm(User *_user, QWidget *parent = nullptr, QTcpSocket* _Socket = nullptr);
    ~RegForm();

private slots:
    void SlotRegBtn();
    void SlotAuthBtn();

signals:
    void SignalRegBtn(QString);
    void SignalAuthBtn(QString);
};

#endif // REGFORM_H
