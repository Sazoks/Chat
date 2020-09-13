#ifndef CONFORM_H
#define CONFORM_H

#include "functionalforms.h"
#include <QWidget>
#include <QString>
#include <QTcpSocket>
#include <QMessageBox>

namespace Ui {
class ConForm;
}

class ConForm : public QWidget
{
    Q_OBJECT
private:
    Ui::ConForm *ui;
    QTcpSocket *mTcpSocket;
    FunctionalForms mFunForms;


private slots:
    void SlotConnectBtn();

signals:
    void SignalConnectBtn(QString);

public:
    explicit ConForm(QWidget *parent = nullptr, QTcpSocket *_socket = nullptr);
    ~ConForm();
};

#endif // CONFORM_H
