#include "messagewindow.h"
#include "ui_messagewindow.h"

MessageWindow::MessageWindow(User *_user, QWidget *parent, QTcpSocket *_socket) :
    QWidget(parent),
    ui(new Ui::MessageWindow)
{
    // инициализируем поля
    ui->setupUi(this);
    mUser = _user;

    // создаем сокет для передачи сообщений
    mTcpSocket = _socket;
    connect(ui->SendMsgBtn, &QPushButton::clicked, this, &MessageWindow::SendMessage);
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MessageWindow::ReadMessage);

    // настройки таблицы
    ui->tableWidget->setEditTriggers(nullptr); // запретили редактирование ячеек
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection); // разрешили выделение только одного элемента
    ui->tableWidget->setHorizontalHeaderLabels({"Messages"});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->setStyleSheet("font-size: 18px;");
}

MessageWindow::~MessageWindow()
{
    disconnect(mTcpSocket, &QTcpSocket::readyRead, this, &MessageWindow::ReadMessage);
    mFunForms.SendData(mTcpSocket, "DisconnectChan"); // сигнал об отключении от канала
    mFunForms.GetData(mTcpSocket);
    delete ui;
}

// private slots
void MessageWindow::SendMessage()
{
    QString str = ui->MsgEdit->text();
    if (str.size() > 60) {
        mFunForms.ShowMessage("The sentence is too long");
        return;
    }
    mFunForms.SendData(mTcpSocket, ("msg:" + ui->MsgEdit->text()).toLocal8Bit());
    ui->MsgEdit->clear();
}

void MessageWindow::ReadMessage()
{
    // принимаем сообщение
    QByteArray Block;
    Block.append(mTcpSocket->readAll());

    // вставляем сообщение в таблицу
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(Block);
    item->setTextAlignment(Qt::AlignLeft);

    // выводим на экран
    int RowCount = ui->tableWidget->rowCount() + 1;
    ui->tableWidget->setRowCount(RowCount);
    ui->tableWidget->setItem(RowCount - 1, 0, item);
}
