#ifndef LISTCHANNELS_H
#define LISTCHANNELS_H

#include "user.h"
#include "functionalforms.h"
#include "channel.h"
#include <QWidget>
#include <QTcpSocket>
#include <QList>
#include <QByteArray>

namespace Ui {
class ListChannels;
}

class ListChannels : public QWidget
{
    Q_OBJECT
private:
    User *mUser;
    QList<Channel> mChannels;

    FunctionalForms mFunForms;
    Ui::ListChannels *ui;
    QTcpSocket *mTcpSocket;
    int CountChannels;
    int IndexSelectionChan;

    // служебные функции
    int GetCountChannels(QByteArray) const;

private slots:
    void SlotUploadMoreChan();
    void SlotIndexChanForConnect();
    void SlotConnectToChan();

signals:
    void SignalInitMsgWindow();

public:
    explicit ListChannels(User *_user, QWidget *parent = nullptr, QTcpSocket *_socket = nullptr);
    ~ListChannels();
};

#endif // LISTCHANNELS_H
