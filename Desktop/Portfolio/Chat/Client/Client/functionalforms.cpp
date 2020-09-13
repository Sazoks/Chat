#include "functionalforms.h"

FunctionalForms::FunctionalForms(QWidget *parent)
    : QWidget(parent) {}

void FunctionalForms::ShowMessage(QString _text)
{
    QMessageBox Message;
    Message.setText(_text);
    Message.exec();
}

QByteArray FunctionalForms::GetData(QTcpSocket *_sock)
{
    QByteArray Block;
    _sock->waitForReadyRead();
    while (_sock->bytesAvailable() > 0)
        Block.append(_sock->readAll());
    return Block;
}

bool FunctionalForms::EmitSignalToServer(const QByteArray &_command, QTcpSocket *_sock)
{
    SendData(_sock, _command);
    QByteArray Block = GetData(_sock);
    if (Block != "0") {
        ShowMessage(Block);
        return false;
    }
    return true;
}

void FunctionalForms::SendData(QTcpSocket *_sock, const QByteArray &msg)
{
    _sock->write(msg);
}
