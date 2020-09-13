#ifndef FUNCTIONALFORMS_H
#define FUNCTIONALFORMS_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QThread>

class FunctionalForms : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionalForms(QWidget *parent = nullptr);

    // функционал
    QByteArray GetData(QTcpSocket*);
    void SendData(QTcpSocket*, const QByteArray&);
    void ShowMessage(QString);
    bool EmitSignalToServer(const QByteArray&, QTcpSocket*);
};

#endif // FUNCTIONALFORMS_H
