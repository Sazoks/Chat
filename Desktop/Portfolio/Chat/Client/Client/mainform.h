#ifndef MAINFORM_H
#define MAINFORM_H

#include "profileform.h"
#include "listchannels.h"
#include "mychan.h"
#include "user.h"
#include "functionalforms.h"
#include "messagewindow.h"
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QTcpSocket>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT
private:
    User *mUser;
    QTcpSocket *mSocket;
    Ui::MainForm *ui;
    FunctionalForms mFunForms;

    // формы
    ProfileForm *mProfileForm;
    ListChannels *mListChannels;
    MyChan *mMyChan;
    MessageWindow *mMsgWindow;

    void DeleteCurrentWidget();

private slots:
    void InitSettingsForm();
    void InitMyChanForm();
    void InitListChanForm();
    void InitMsgWindow();
    void SlotExit();
    void UpdateMenu();

signals:
    void SignalExit(QString);

public:
    explicit MainForm(User *_user, QWidget *parent = nullptr, QTcpSocket *_socket = nullptr);
    ~MainForm();
};

#endif // MAINFORM_H
