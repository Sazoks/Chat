#include "mainform.h"
#include "ui_mainform.h"
#include <QByteArray>

MainForm::MainForm(User *_user, QWidget *parent, QTcpSocket *_socket) :
    QWidget(parent),
    mUser(_user),
    mSocket(_socket),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    UpdateMenu();
    ui->MyChanBtn->setText((mUser->GetAvailChan() ? "My channel" : "Create channel!"));

    mProfileForm = nullptr;
    mListChannels = nullptr;
    mMyChan = nullptr;
    mMsgWindow = nullptr;

    connect(ui->ProfileBtn, &QPushButton::clicked, this, &MainForm::InitSettingsForm);
    connect(ui->MyChanBtn, &QPushButton::clicked, this, &MainForm::InitMyChanForm);
    connect(ui->CreateChatBtn, &QPushButton::clicked, this, &MainForm::InitListChanForm);
    connect(ui->ExitBtn, &QPushButton::clicked, this, &MainForm::SlotExit);
}

MainForm::~MainForm()
{
    DeleteCurrentWidget();
    delete ui;
}

void MainForm::DeleteCurrentWidget()
{
    if (mProfileForm) {
        delete mProfileForm;
        mProfileForm = nullptr;
    }
    if (mListChannels) {
        delete mListChannels;
        mListChannels = nullptr;
    }
    if (mMyChan) {
        delete mMyChan;
        mMyChan = nullptr;
    }
    if (mMsgWindow) {
        delete mMsgWindow;
        mMsgWindow = nullptr;
    }
}


// slots
void MainForm::UpdateMenu()
{   
    ui->LabelUsername->setText(mUser->GetUserName());
    ui->LabelUsername->setStyleSheet("font-size: 18px;");
    if (mUser->GetAvailChan()) ui->MyChanBtn->setText("My channel");
    else ui->MyChanBtn->setText("Create channel!");
}

void MainForm::SlotExit()
{
    DeleteCurrentWidget();
    mFunForms.SendData(mSocket, "LogoutOfProfile");
    emit SignalExit("Exit");
}

void MainForm::InitMsgWindow()
{
    DeleteCurrentWidget();
    mMsgWindow = new MessageWindow(mUser, this, mSocket);
    ui->MainLayout->addWidget(mMsgWindow, 0, 2);
}

void MainForm::InitSettingsForm()
{
    DeleteCurrentWidget();
    UpdateMenu();
    mProfileForm = new ProfileForm(mUser, this, mSocket);
    connect(mProfileForm, &ProfileForm::SignalChangeUsername, this, &MainForm::UpdateMenu);
    ui->MainLayout->addWidget(mProfileForm, 0, 2);
}

void MainForm::InitMyChanForm()
{
    // проверка на наличие канала
    if (!mUser->GetAvailChan()) {
        // посылаем серверу запрос на создание нового канала
        if (!mFunForms.EmitSignalToServer("CreateChan", mSocket)) return;

        mUser->SetAvailChan(true);
        //mMyChan->SetDefaultSettings();
        mFunForms.ShowMessage("You created youre first channel!\nHe have standart settings:\nName - Channel#1\nMax count users - 1\nPassword - no password\nYou can set up your channel right now");
    }

    // удаляем текущий виджет
    DeleteCurrentWidget();

    // создаем окно настроек канала
    mMyChan = new MyChan(mUser, this, mSocket);
    connect(mMyChan, &MyChan::SignalDeletedChan, this, &MainForm::InitSettingsForm);
    connect(mMyChan, &MyChan::SignalInitMsgWindow, this, &MainForm::InitMsgWindow);
    ui->MyChanBtn->setText("My channel");
    ui->MainLayout->addWidget(mMyChan, 0, 2);
}

void MainForm::InitListChanForm()
{
    DeleteCurrentWidget();
    mListChannels = new ListChannels(mUser, this, mSocket);
    connect(mListChannels, &ListChannels::SignalInitMsgWindow, this, &MainForm::InitMsgWindow);
    ui->MainLayout->addWidget(mListChannels, 0, 2);
}
