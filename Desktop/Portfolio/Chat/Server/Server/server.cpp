#include "server.h"
#include <QMutexLocker>

Server::Server(quint16 _Port)
    : MAX_CONNECTION(100)
{
    // инициализируем драйвер базы данных
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName("SQLite\\DB\\Program\\db.sqlite");

    // инициализация активных каналов
    if (!InitActiveChannels()) {
        qDebug() << "Init channel error";
        return;
    }

    // инициализация массива указателей на юзеров
    mUsers.reserve(MAX_CONNECTION);
    for (int i = 0; i < MAX_CONNECTION; i++)
        mUsers.append(nullptr);

    // инициализация тригеров функций
    InitCommandsList();

    // при новом подключении запускаем функцию сохранения соединения
    connect(this, &QTcpServer::newConnection, this, &Server::ConnectClient);

    // запуск сервера
    if (!listen(QHostAddress::Any, _Port)) qDebug() << "Start listen: FAILED\n";
    else qDebug() << "Start listen: OK\n";
}
int Server::CountConnection = 0;


Server::~Server()
{
    // аварийная остановка всех работающих потоков, удаление работников и самих потоков.
   for (int i = 0; i < MAX_CONNECTION; i++)
       if (mUsers[i] != nullptr)
           delete mUsers[i];
   // удаление каналов
   for (int i = 0; i < mChannels.size(); i++)
       delete mChannels[i];
   // закрытие сервера
   close();
}


void Server::ConnectClient()
{
    // берем следующее подеключение
    QTcpSocket *_socket = nextPendingConnection();

    // если нет мест в пуле, закрываем соединение
    if (CountConnection == MAX_CONNECTION) {
        _socket->close();
        return;
    }

    // выводим сообщение о новом подключении и увеличиваем счетчик юзеров
    CountConnection++;
    qDebug() << "New connection\n" << "Active connection: " << CountConnection << '\n';

    // ищем свободное место в пуле
    int IndFreePlace = -1;
    for (int i = 0; i < MAX_CONNECTION; i++)
        if (!mUsers[i]) {
            IndFreePlace = i;
            break;
        }

    // добавляем юзера в список, делаем connect'ы
    mUsers[IndFreePlace] = new User(_socket, IndFreePlace);
    connect(mUsers[IndFreePlace], &User::SignalMyReadyRead, this, &Server::CommandHandler);
    connect(mUsers[IndFreePlace], &User::SignalMyDisconnect, this, &Server::DisconnectClient);
    SendData(mUsers[IndFreePlace], "1");
}

void Server::DisconnectClient(int _id)
{
    // удаляем юзера из канала
    if (mUsers[_id]->GetCurrentChannel())
        mUsers[_id]->GetCurrentChannel()->DeleteUser(mUsers[_id]->GetUserName());

    // обнуляем элемент списка
    qDebug() << "Client " << mUsers[_id]->GetUserName() << " disconnected\n";
    mUsers[_id]->deleteLater();
    mUsers[_id] = nullptr;

    // вывод информации ою активных подключениях
    CountConnection--;
    qDebug() << "Active connection: " << CountConnection << '\n';
}

void Server::CommandHandler()
{
    // получаем отправителя сигнала
    User *_tempUser = qobject_cast<User*>(sender());

    // прием запроса от клиента
    QByteArray Block;
    Block.append(_tempUser->GetTcpSocket()->readAll());

    // ищем функцию в ассоциативном массиве и выполняем ееы
    It = Functions.find(Block);
    // вызываем указатель на фукнцию-член ИМЕННО ТАК!
    if (It != Functions.end())
        (this->*It.value())(_tempUser);
    else if (Block.split(':')[0] == "msg") // иначе если это сообщение, то отправляем сразу всем пользователям на канале
        _tempUser->GetCurrentChannel()->SendMsgToUsers(Block.mid(4, Block.size() - 4), _tempUser->GetUserName());
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

void Server::InitCommandsList()
{
    Functions["Auth"]               =   &Server::Authorized;
    Functions["Reg"]                =   &Server::Registration;
    Functions["ChangeNU"]           =   &Server::ChangeName_User;
    Functions["ChangePU"]           =   &Server::ChangePassword_User;
    Functions["CreateChan"]         =   &Server::CreateChan;
    Functions["ChangeNC"]           =   &Server::ChangeName_Channel;
    Functions["ChangePC"]           =   &Server::ChangePassword_Channel;
    Functions["SetCountU"]          =   &Server::SetNewMaxCountUsers;
    Functions["DeleteChan"]         =   &Server::DeleteCannel;
    Functions["UploadChan"]         =   &Server::UploadChannels;
    Functions["LogoutOfProfile"]    =   &Server::LogoutOfProfile;
    Functions["GetStateChan"]       =   &Server::GetStateChan;
    Functions["ChangeStateChannel"] =   &Server::ChangeStateChannel;
    Functions["ConnectToChan"]      =   &Server::ConnectToChan;
    Functions["DisconnectChan"]     =   &Server::DisconnectChan;
}



QByteArray Server::GetData(User *_user)
{

    QTcpSocket *_sock = _user->GetTcpSocket();
    QByteArray Block;
    _sock->waitForReadyRead();
    while (_sock->bytesAvailable() > 0)
        Block.append(_sock->readAll());
    return Block;
}

void Server::SendData(User *_user, const QByteArray &msg)
{
    //QThread::msleep(500);
    _user->GetTcpSocket()->write(msg);
}

void Server::ConnectToDB(User *_user)
{
    // соединяемся с БД
    // выводим ошибку и сообщаем пользователю об этом, закрывая с ним соединение, в случае ошибки
    if (!mDatabase.open()) {
        qDebug() << mDatabase.lastError().text();
        SendData(_user, "DATABASE ERROR");
        return;
    }
    SendData(_user, "0");
}

void Server::ChangeStateChannel(User *_user)
{
    // подключаемся к бд и ждем данные от юзера
    ConnectToDB(_user);
    QByteArray Block = GetData(_user);

    /*
     * Если клиент останавливает канал (т.е. код = 0),
     * обновляем запись в бд, затем в цикле ищем канал,
     * у которого владелец равен нашему юзеру (по имени),
     * и удаляем сначала канал, а затем сам указтель на этот канал
     * из массива
     *
     * Если код = 1, тогда берем канал из бд, по этим
     * данным создаем новый элемент в массиве и обновляем
     * параметр worked у канала в бд
     */
    QString _username = _user->GetUserName();
    QSqlQuery _query;
    if (Block == "0") {
        _query.exec("UPDATE Channels SET worked=false WHERE owner='" + _username + "'");
        for (int i = 0; i < mChannels.size(); i++)
            if (mChannels[i]->GetOwner() == _username) {
                delete mChannels[i];
                mChannels.removeAt(i);
            }
    }
    else {
        _query.exec("SELECT name,password,maxUsers FROM Channels WHERE owner='" + _username + "'");
        _query.first();
        mChannels.append(new Channel(_query.value(0).toString(), _query.value(1).toString(), _username, _query.value(2).toInt()));
        _query.exec("UPDATE Channels SET worked=true WHERE owner='" + _username + "'");
    }
    mDatabase.close();
}

void Server::GetStateChan(User *_user)
{
    ConnectToDB(_user);
    QSqlQuery _query;
    _query.exec("SELECT worked FROM Channels WHERE owner='" + _user->GetUserName() + "'");
    _query.first();
    GetData(_user); // ждем готовность клиента для принятия данных
    SendData(_user, (_query.value(0).toBool() ? "1" : "0"));
    mDatabase.close();
}

void Server::LogoutOfProfile(User *_user)
{
    _user->SetUsername("");
    _user->SetAvailChan(false);
    _user->SetCurrentChannel(nullptr);
}

void Server::CreateChan(User *_user)
{
    // захватываем доступ к списку каналов для безопасного редактирования
    //QMutexLocker _locker(mMutex);

    // соединяемся с БД и отсылаем ответ клиенту
    ConnectToDB(_user);

    // устанавливаем флаг о наличии канала в true
    _user->SetAvailChan(true);
    // обнавляем данные в базе данных
    QSqlQuery _query;
    _query.exec("UPDATE Clients SET avchan=1 WHERE username='" + _user->GetUserName() + "'");
    //создаем канал в таблице Channels
    _query.exec("INSERT INTO Channels VALUES('Channel#1', NULL, 1, '" + _user->GetUserName() + "', false)");
    mDatabase.close();
}

void Server::UploadChannels(User *_user)
{
    // соединяемся с БД и отсылаем ответ клиенту
    ConnectToDB(_user);

    // смотрим, нужно ли обнулять счетчик
    QByteArray Block = GetData(_user);
    if (Block == "0") _user->SetCountUpload(0);

    // получаем данные из БД : name,maxUsers,owner,password
    QSqlQuery _query;
    _query.exec("SELECT name,maxUsers,owner,password FROM Channels WHERE worked=true LIMIT 5 OFFSET " + QString::number(5 * _user->GetCountUpload())); // statc_cast<QString> почему-то не работает!
    // увеличиваем счетчик
    _user->SetCountUpload(_user->GetCountUpload() + 1);

    // записываем все в один блок байтов
    Block = "";
    while (_query.next())
        Block.append(_query.value(0).toString() + ';' + _query.value(1).toString() + ';' + _query.value(2).toString() + ';' + (_query.value(3).toString() == "" ? "0" : "1") + '%');
    if (Block == "") Block = "-";

    // отправляем данные клиенту
    SendData(_user, Block);
    mDatabase.close();
}

void Server::ChangeName_Channel(User *_user)
{
    ConnectToDB(_user);
    // принимаем данные от клиента
    QByteArray Block = GetData(_user);

    // меняем имя канала
    QSqlQuery _query;
    if (_query.exec("UPDATE Channels SET name='" + Block + "' WHERE owner='" + _user->GetUserName() + "'")) {

        SendData(_user, "OK");
    }
    else SendData(_user, "FAILED");
    mDatabase.close();
}

void Server::ChangePassword_Channel(User *_user)
{
    ConnectToDB(_user);
    // принимаем данные от клиента
    QByteArray Block = GetData(_user);
    QString _oldPass = Block.split(';')[0];
    QString _newPass = Block.split(';')[1];

    // проверка старого пароля
    QSqlQuery _query;
    _query.exec("SELECT password FROM Channels WHERE owner='" + _user->GetUserName() + "'");
    _query.first();
    if (_oldPass != _query.value(0).toString()) {
        SendData(_user, "0");
        return;
    }

    // меняем пароль в БД
    if (_query.exec("UPDATE Channels SET password='" + _newPass + "' WHERE owner='" + _user->GetUserName() + "'"))
        SendData(_user, "1");
    else SendData(_user, "0");
    mDatabase.close();
}

void Server::SetNewMaxCountUsers(User *_user)
{
    ConnectToDB(_user);
    // принимаем данные от клиента
    QByteArray Block = GetData(_user);

    // обновляем запись в БД
    QSqlQuery _query;
    if (_query.exec("UPDATE Channels SET maxUsers=" + Block + " WHERE owner='" + _user->GetUserName() + "'")) {

        SendData(_user, "0");
    }
    else SendData(_user, "1");
    mDatabase.close();
}

void Server::DeleteCannel(User *_user)
{
    ConnectToDB(_user);
    bool Controller = true;
    QSqlQuery _query;
    Controller = _query.exec("UPDATE Clients SET avchan=0 WHERE username='" + _user->GetUserName() + "'");
    Controller = _query.exec("DELETE FROM Channels WHERE owner='" + _user->GetUserName() + "'");
    GetData(_user); // принимаем ответ о готовности клента к принятию ответа
    SendData(_user, (Controller ? "0" : "1"));
    if (Controller) _user->SetAvailChan(false);
    mDatabase.close();
}

void Server::ConnectToChan(User *_user)
{
    // сообщаем клиенту о успешном вхождении в функцию
    SendData(_user, "0");

    // принимаем имя владельца канала, к которому подключаемся, и сохраняем указатель на него
    QByteArray Block = GetData(_user);
    int _index = -1; // - текущий канал
    for (int i = 0; i < mChannels.size(); i++)
        if (mChannels[i]->GetOwner() == Block) {
            _index = i;
            break;
        }

    // если канал не работает (т.е. не был найден в массиве)
    if (_index == -1) {
        SendData(_user, "-1");
        return;
    }
    // проверка на макс. кол-во юзеров
    if (!mChannels[_index]->AvailFreePlace()) {
        SendData(_user, "0");
        _user->SetCurrentChannel(nullptr);
        return;
    }
    if (mChannels[_index]->AvailPassword()) {
        SendData(_user, "1");
        // получаем пароль на проверку
        Block = GetData(_user);
        if (!mChannels[_index]->CheckPassword(Block)) {
            SendData(_user, "2");
            _user->SetCurrentChannel(nullptr);
            return;
        }
    }

    // в случае успешного прохождения всех проверок подключаемся
    SendData(_user, "3");
    mChannels[_index]->AddUser(_user);
    _user->SetCurrentChannel(mChannels[_index]);
}

void Server::DisconnectChan(User *_user)
{
    _user->GetCurrentChannel()->DeleteUser(_user->GetUserName());
    _user->SetCurrentChannel(nullptr);
    SendData(_user, "/exit"); // сигнал об успешном отключении
}

void Server::ChangePassword_User(User *_user)
{
    ConnectToDB(_user);
    // принимаем данные от клиента
    QByteArray Block = GetData(_user);
    QString _oldPass = Block.split(';')[0];
    QString _newPass = Block.split(';')[1];

    // проверка старого пароля
    QSqlQuery _query;
    _query.exec("SELECT username,password FROM Clients WHERE username='" + _user->GetUserName() + "'");
    _query.first();
    if (_oldPass != _query.value(1)) {
        SendData(_user, "OLD PASSWORD IS WRONG");
        return;
    }

    SendData(_user, "1");
    // меняем пароль на новый
    _query.exec("UPDATE Clients SET password='" + _newPass + "' WHERE username='" + _user->GetUserName() + "'");
    mDatabase.close();
}

void Server::ChangeName_User(User *_user)
{
    ConnectToDB(_user);
    // принимаем данные от клиента
    QByteArray Block = GetData(_user);

    // Ищем совпадение имени в БД
    QSqlQuery _query;
    _query.exec("SELECT username FROM Clients WHERE username='" + Block + "'");
    bool ControlPassed = true;
    if (_query.next()) ControlPassed = false;

    // отправляем ответ клиенту
    if (ControlPassed) {
        QString _lastUsername = _user->GetUserName(); // сохраняем старое имя для поиска по бд. оно - primary ky
        _user->SetUsername(Block);
        _query.exec("UPDATE Clients SET username='" + Block + "' WHERE username='" + _lastUsername + "'");
        _query.exec("UPDATE Channels SET owner='" + Block + "' WHERE owner='" + _lastUsername + "'");
        SendData(_user, "1");
    }
    else SendData(_user, "0");
    mDatabase.close();
}


void Server::Registration(User *_user)
{
    ConnectToDB(_user);
    // принимаем данные от клиента
    QByteArray Block = GetData(_user);
    QString _Username = Block.split(';')[0];
    QString _Password = Block.split(';')[1];

    // проверка уникальности ника в БД
    QSqlQuery _query;
    _query.exec("SELECT username,password,avchan FROM Clients WHERE username='" + _Username + "'");
    bool ControlPassed = true;
    if (_query.next()) ControlPassed = false;

    // отправляем клиенту результат регистрации
    if (ControlPassed) {
        _query.exec("INSERT INTO Clients VALUES('" + _Username + "', '" + _Password + "', false)");
        _user->SetUsername(_Username);
        _user->SetAvailChan(false);
        SendData(_user, "0");
    }
    else SendData(_user, "ERROR REGISTRATION\nTRY AGAIN");
    mDatabase.close();
}


void Server::Authorized(User *_user)
{
    ConnectToDB(_user);
    // принимаем данные от клиента
    QByteArray Block = GetData(_user);
    QString _Username = Block.split(';')[0];
    QString _Password = Block.split(';')[1];

    // проверка данных в БД
    QSqlQuery _query;
    _query.exec("SELECT username,password,avchan FROM Clients WHERE username='" + _Username + "' AND password='" + _Password + "'");
    bool ControlPassed = false;
    if (_query.next()) ControlPassed = true;

    // отправляем клиенту результат входа и закрываем соединение с БД
    if (ControlPassed) {

        _user->SetUsername(_Username);
        _user->SetAvailChan(_query.value(2).toBool());

        // в случае успеха пароль и имя, отправленные клиентов, уже есть на клиентской стороне
        // поэтому отправим только состояние наличия канала у юзера
        SendData(_user, (_user->GetAvailChan() ? "1" : "0"));
    }
    else SendData(_user, "ERROR AUTHORIZED");
    mDatabase.close();
}

