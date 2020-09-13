#include "server.h"
#include <QMutexLocker>

Server::Server(quint16 _Port)
    : MAX_CONNECTION(10)
{
    // инициализируем драйвер базы данных
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName("SQLite\\DB\\Program\\db.sqlite");

    // инициализация каналов
    if (!InitActiveChannels()) {
        qDebug() << "Init channel error";
        return;
    }

    // создаем потоки
    Workers.reserve(MAX_CONNECTION);
    Threads.reserve(MAX_CONNECTION);
    for (int i = 0; i < MAX_CONNECTION; i++) {
        Threads.append(new QThread);
        Workers.append(nullptr);
    }

    // при новом подключении запускаем функцию выделения нового потока
    connect(this, &QTcpServer::newConnection, this, &Server::ConnectClient);

    // запуск сервера
    if (!listen(QHostAddress::Any, _Port)) qDebug() << "Start listen: FAILED\n";
    else qDebug() << "Start listen: OK\n";
}
int Server::CountConnection = 0;


Server::~Server()
{
    // аварийная остановка всех работающих потоков, удаление работников и самих потоков.
   for (int i = 0; i < MAX_CONNECTION; i++) {
       if (Threads[i]->isRunning()) {
           Threads[i]->terminate();
           delete Workers[i];
       }
       delete Threads[i];
   }
   // удаление каналов
   for (int i = 0; i < mChannels.size(); i++)
       delete mChannels[i];
   // закрытие сервера
   close();
}


void Server::ConnectClient()
{
    // захватываем мьютекс
    QMutexLocker _locker(&mMutex);

    // берем след подеключение
    QTcpSocket *_Socket = nextPendingConnection();

    // если нет мест в пуле, закрываем соединение
    if (CountConnection == 10) {
        _Socket->close();
        return;
    }

    qDebug() << "New connection\n";
    CountConnection++;

    // ищем свободное место в пуле
    int IndFreePlace = -1;
    for (int i = 0; i < MAX_CONNECTION; i++)
        if (!Threads[i]->isRunning()) {
            IndFreePlace = i;
            break;
        }

    // создаем обработчик и помещаем его в поток
    Workers[IndFreePlace] = new Worker(_Socket->socketDescriptor(), IndFreePlace, &mDatabase, mChannels, &mMutex);
    Workers[IndFreePlace]->moveToThread(Threads[IndFreePlace]);

    // настраиваем сигналы и слоты потока и обработчика. запускаем поток.
    connect(Threads[IndFreePlace], &QThread::started, Workers[IndFreePlace], &Worker::StartWork);
    connect(Workers[IndFreePlace], &Worker::StopThread, this, &Server::DisconnectClient);
    Threads[IndFreePlace]->start();

    qDebug() << "Active connection: " << CountConnection << '\n';
}


void Server::DisconnectClient(int ThreadID)
{
    CountConnection--;

    // останавливаем поток и удаляем обработчик
    Threads[ThreadID]->quit();
    Threads[ThreadID]->wait();
    delete Workers[ThreadID];
    Workers[ThreadID] = nullptr;

    // вывод информации о потоках
    qDebug() << "Active connection: " << CountConnection << '\n';
    for (int i = 0; i < MAX_CONNECTION; i++)
        if (Threads[i]->isRunning()) qDebug() << "Thread #"<<i<<" RUN\n";
        else qDebug() << "Thread #"<<i<<" STOP\n";
}

bool Server::InitActiveChannels()
{
    // подключение к бд
    if (!mDatabase.open()) {
        qDebug() << mDatabase.lastError().text();
        return false;
    }

    // создание запроса
    QSqlQuery _query;
    _query.exec("SELECT name,password,maxUsers,owner FROM Channels WHERE worked=true");

    // инициализация работающих каналов
    while (_query.next())
        mChannels.append(new Channel(_query.value(0).toString(), _query.value(1).toString(), _query.value(3).toString(), _query.value(2).toInt()));

    // закрытие соединение с бд
    mDatabase.close();
    return true;
}
