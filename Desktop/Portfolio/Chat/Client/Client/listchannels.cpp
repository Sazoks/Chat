#include "listchannels.h"
#include "ui_ListChannels.h"
#include <QInputDialog>

ListChannels::ListChannels(User *_user, QWidget *parent, QTcpSocket *_socket) :
    QWidget(parent),
    ui(new Ui::ListChannels),
    CountChannels(-1),
    IndexSelectionChan(-1)
{
    ui->setupUi(this);
    mUser = _user;
    mTcpSocket = _socket;

    // connect'ы
    connect(ui->UploadMoreChan, &QPushButton::clicked, this, &ListChannels::SlotUploadMoreChan);
    connect(ui->tableWidget, &QTableWidget::clicked, this, &ListChannels::SlotIndexChanForConnect);
    connect(ui->ConnectToChanBtn, &QPushButton::clicked, this, &ListChannels::SlotConnectToChan);

    // настройки таблицы
    ui->tableWidget->setEditTriggers(nullptr); // запретили редактирование ячеек
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); // разрешили выделение только одного элемента
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); // говорим, что хотим выделять при нажатии ВСЮ СТРОКУ
    ui->tableWidget->setHorizontalHeaderLabels({"Name", "Count users", "Password"});
    //ui->tableWidget->horizontalHeader()->setStretchLastSection(true); // растягиваем последний заголовок на всю оставшуюся ширину
    // растягиваем элементы равномерно
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    // инициализация первых 5-ти каналлов в таблице
    SlotUploadMoreChan();
}

ListChannels::~ListChannels()
{
    delete ui;
}

// private slots
void ListChannels::SlotUploadMoreChan()
{
    if (!mFunForms.EmitSignalToServer("UploadChan", mTcpSocket)) {
        mFunForms.ShowMessage("Error upload channels");
        return;
    }

    // если мы открыли первый раз страницу каналов, посылаем 0
    // иначе посылаем 1, и это означает, что мы запросили больше каналов
    // нажав на кнопку Upload more channels
    mFunForms.SendData(mTcpSocket, (CountChannels == -1 ? "0" : "1"));

    // принимаем данные
    QByteArray Block = mFunForms.GetData(mTcpSocket);
    // узнаем, сколько каналов пришло по факту
    int PULL_CHANNELS = GetCountChannels(Block);
    // кол-во строк в таблице
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + PULL_CHANNELS);

    for (int i = 0; i < PULL_CHANNELS; i++) {
        // очередной канал
        mChannels.append(Channel(Block.split('%')[i].split(';')));
        CountChannels++;

        // заполняем таблицу
        // имя
        QTableWidgetItem *ColName = new QTableWidgetItem;
        ColName->setText((mChannels[CountChannels].GetOwner() + '@' + mChannels[CountChannels].GetName()));
        ColName->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(CountChannels, 0, ColName);

        // кол-во юзеров
        QTableWidgetItem *ColMaxUsers = new QTableWidgetItem;
        ColMaxUsers->setText(mChannels[CountChannels].GetMaxUsers());
        ColMaxUsers->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(CountChannels, 1, ColMaxUsers);

        // наличие пароля
        QTableWidgetItem *ColAvpass = new QTableWidgetItem;
        ColAvpass->setText((mChannels[CountChannels].GetAvpass() == "0" ? "No" : "Yes"));
        ColAvpass->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(CountChannels, 2, ColAvpass);
    }
}

void ListChannels::SlotIndexChanForConnect()
{
    // в _selectModel получаем список всех выделенных элементов
    // т.к. мы точно знаем. что у нас одна выделенная СТРОКА
    // мы без цикла в уловии проверяем на наличие выделеных элементов,
    // берем выделенные СТРОКИ в _selectModel, берем ПЕРВЫЙ И ЕДИНСТВЕННЫЙ
    // ЭЛЕМЕНТ и берем номер строки
    QItemSelectionModel *_selectModel = ui->tableWidget->selectionModel();
    if (_selectModel->hasSelection())
        IndexSelectionChan = _selectModel->selectedRows().first().row();
}

void ListChannels::SlotConnectToChan()
{
    // если не выбран ни один канал
    if (IndexSelectionChan == -1) {
        mFunForms.ShowMessage("Select the channel");
        return;
    }

    // посылаем сигнал серверу о подключении
    if (!mFunForms.EmitSignalToServer("ConnectToChan", mTcpSocket)) {
        mFunForms.ShowMessage("Error connection");
        return;
    }

    // берем имя владельца канала (оно служит нам ID для каналов) и отправляем на сервер
    QByteArray Block = mChannels[IndexSelectionChan].GetOwner().toLocal8Bit();
    mFunForms.SendData(mTcpSocket, Block);

    // проверка на свободные места и пароля
    Block = mFunForms.GetData(mTcpSocket);
    if (Block == "-1") {
        mFunForms.ShowMessage("Sorry, channel dont work\nTry update list");
        return;
    }
    if (Block == "0") {
        mFunForms.ShowMessage("Dont free place");
        return;
    }
    if (Block == "1") {
        // запрашиваем пароль
        bool ok;
        Block = QInputDialog::getText(this, "Enter the password", "Password", QLineEdit::Normal, "", &ok).toLocal8Bit();
        if (!ok) Block = "-1";
        mFunForms.SendData(mTcpSocket, Block);
        // ждем ответа
        Block = mFunForms.GetData(mTcpSocket);
        if (Block == "2") {
            mFunForms.ShowMessage("Wrong the password");
            return;
        }
    }

    // посылаем сигнал об инициализации окна переписки
    emit SignalInitMsgWindow();
}

// служебные функции
int ListChannels::GetCountChannels(QByteArray _block) const
{
    int Count = 0;
    for (int i = 0; i < _block.size(); i++)
        if (_block[i] == '%')
            Count++;
    return Count;
}

