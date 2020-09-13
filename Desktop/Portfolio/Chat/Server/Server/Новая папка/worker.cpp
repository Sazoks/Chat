#include "worker.h"
#include "channel.h"
#include <QByteArray>
#include <QMutexLocker>

Worker::Worker(qintptr SockD, int ID, QSqlDatabase *SourceDB, QList<Channel*> &Channels, QMutex *_mutex)
    : mDatabase(SourceDB),
      mSockD(SockD),
      mID(ID),
      CountUpload(0),
      mChannels(Channels),
      mMutex(_mutex)
{
    // инициализируем QMap фукнций для обработки запросов пользователя
    Functions["Auth"]               =   &Worker::Authorized;
    Functions["Reg"]                =   &Worker::Registration;
    Functions["ChangeNU"]           =   &Worker::ChangeName_User;
    Functions["ChangePU"]           =   &Worker::ChangePassword_User;
    Functions["CreateChan"]         =   &Worker::CreateChan;
    Functions["ChangeNC"]           =   &Worker::ChangeName_Channel;
    Functions["ChangePC"]           =   &Worker::ChangePassword_Channel;
    Functions["SetCountU"]          =   &Worker::SetNewMaxCountUsers;
    Functions["DeleteChan"]         =   &Worker::DeleteCannel;
    Functions["UploadChan"]         =   &Worker::UploadChannels;
    Functions["LogoutOfProfile"]    =   &Worker::LogoutOfProfile;
    Functions["GetStateChan"]       =   &Worker::GetStateChan;
    Functions["ChangeStateChannel"] =   &Worker::ChangeStateChannel;
    Functions["ConnectToChan"]      =   &Worker::ConnectToChan;
}


Worker::~Worker()
{
    delete mUserSocket;
}

void Worker::printData()
{
    qDebug() <<"ID: " << mID <<'\n'
            << "User: " << mUser.GetUserName() <<'\n';
}

void Worker::StartWork()
{
    // создаем сокет по дескриптору
    mUserSocket = new QTcpSocket;
    mUserSocket->setSocketDescriptor(mSockD);

    // при поступлении данных вызываем обработчик команд
    while (true) {
        // прием запроса от клиента
        QByteArray Block = GetData();

        // обработка выхода
        if (Block == "/exit") break;

        //обработка запроса
        It = Functions.find(Block);
        if (It != Functions.end())
            (this->*It.value())();  // вызываем указатель на фукнцию-член ИМЕННО ТАК!
    }

    // закрываем соединение и испускаем сигнал о завершении работы работника
    qDebug() << "Client #" << mID << " disconnected\n";
    mUserSocket->close();
    emit StopThread(mID);
}


// служебные функции
QByteArray Worker::GetData()
{
    QByteArray Block;
    mUserSocket->waitForReadyRead();
    while (mUserSocket->bytesAvailable() > 0)
        Block.append(mUserSocket->readAll());
    return Block;
}

void Worker::ConnectToDB()
{
    // соединяемся с БД
    // выводим ошибку и сообщаем пользователю об этом, закрывая с ним соединение, в случае ошибки
    if (!mDatabase->open()) {
        qDebug() << mDatabase->lastError().text();
        mUserSocket->write("DATABASE ERROR");
        return;
    }
    mUserSocket->write("0");
}

void Worker::ChangeStateChannel()
{
    // захватываем доступ к списку каналов для безопасного редактирования
    QMutexLocker _locker(mMutex);

    ConnectToDB();

    qDebug() << mChannels.size() << '\n';
    for (int i = 0; i < mChannels.size(); i++)
        mChannels[i]->PrintData();

    QByteArray Block = GetData();
    if (Block == "0") { // находим наш канал в списке и удаляем его оттуда
        for (int i = 0; i < mChannels.size(); i++)
            if (mChannels[i]->GetOwner() == mUser.GetUserName()) {
                delete mChannels[i];
                mMyChan = nullptr;
                break;
            }
        qDebug() << mChannels.size() << '\n';
        for (int i = 0; i < mChannels.size(); i++)
            mChannels[i]->PrintData();
        Query.exec("UPDATE Channels SET worked=false WHERE owner='" + mUser.GetUserName() + "'");
    }
    else {  // добавляем канал в список
        mChannels.append(mMyChan);
        Query.exec("UPDATE Channels SET worked=true WHERE owner='" + mUser.GetUserName() + "'");
    }
    mDatabase->close();
}

void Worker::GetStateChan()
{
    ConnectToDB();
    Query.exec("SELECT worked FROM Channels WHERE owner='" + mUser.GetUserName() + "'");
    Query.first();
    QByteArray Block = GetData(); // ждем готовность клиента для принятия данных
    mUserSocket->write((Query.value(0).toBool() ? "1" : "0"));
    mDatabase->close();
}

void Worker::LogoutOfProfile()
{
    mUser.SetUsername("");
    mUser.SetAvailChan(false);
    
}

void Worker::CreateChan()
{
    // захватываем доступ к списку каналов для безопасного редактирования
    //QMutexLocker _locker(mMutex);

    // создаем канал, но в список не добавляем, т.к. там хранятся только активные каналы
    mMyChan = new Channel("Channel#1", "", mUser.GetUserName(), 1);

    // соединяемся с БД и отсылаем ответ клиенту
    ConnectToDB();

    // устанавливаем флаг о наличии канала в true
    mUser.SetAvailChan(true);
    // обнавляем данные в базе данных
    Query.exec("UPDATE Clients SET avchan=1 WHERE username='" + mUser.GetUserName() + "'");
    //создаем канал в таблице Channels
    Query.exec("INSERT INTO Channels VALUES('Channel#1', NULL, 1, '" + mUser.GetUserName() + "', false)");
    mDatabase->close();
}

void Worker::UploadChannels()
{
    // соединяемся с БД и отсылаем ответ клиенту
    ConnectToDB();

    // смотрим, нужно ли обнулять счетчик
    QByteArray Block = GetData();
    if (Block == "0") CountUpload = 0;

    // получаем данные из БД : name,maxUsers,owner,password
    Query.exec("SELECT name,maxUsers,owner,password FROM Channels WHERE worked=true LIMIT 5 OFFSET " + QString::number(5 * CountUpload)); // statc_cast<QString> почему-то не работает!
    // увеличиваем счетчик
    CountUpload++;

    // записываем все в один блок байтов
    Block = "";
    while (Query.next())
        Block.append(Query.value(0).toString() + ';' + Query.value(1).toString() + ';' + Query.value(2).toString() + ';' + (Query.value(3).toString() == "" ? "0" : "1") + '%');
    if (Block == "") Block = "-";

    // отправляем данные клиенту
    mUserSocket->write(Block);
    mDatabase->close();
}

void Worker::ChangeName_Channel()
{
    ConnectToDB();
    // принимаем данные от клиента
    QByteArray Block = GetData();

    // меняем имя канала
    if (Query.exec("UPDATE Channels SET name='" + Block + "' WHERE owner='" + mUser.GetUserName() + "'")) {

        mUserSocket->write("OK");
    }
    else mUserSocket->write("FAILED");
    mDatabase->close();
}

void Worker::ChangePassword_Channel()
{
    ConnectToDB();
    // принимаем данные от клиента
    QByteArray Block = GetData();
    QString _oldPass = Block.split(';')[0];
    QString _newPass = Block.split(';')[1];

    // проверка старого пароля
    Query.exec("SELECT password FROM Channels WHERE owner='" + mUser.GetUserName() + "'");
    Query.first();
    if (_oldPass != Query.value(0).toString()) {
        mUserSocket->write("0");
        return;
    }

    // меняем пароль в БД
    if (Query.exec("UPDATE Channels SET password='" + _newPass + "' WHERE owner='" + mUser.GetUserName() + "'"))
        mUserSocket->write("1");
    else mUserSocket->write("0");
    mDatabase->close();
}

void Worker::SetNewMaxCountUsers()
{
    ConnectToDB();
    // принимаем данные от клиента
    QByteArray Block = GetData();

    // обновляем запись в БД
    if (Query.exec("UPDATE Channels SET maxUsers=" + Block + " WHERE owner='" + mUser.GetUserName() + "'")) {
        mUserSocket->write("0");
    }
    else mUserSocket->write("1");
    mDatabase->close();
}

void Worker::DeleteCannel()
{
    ConnectToDB();
    bool Controller = true;
    Controller = Query.exec("UPDATE Clients SET avchan=0 WHERE username='" + mUser.GetUserName() + "'");
    Controller = Query.exec("DELETE FROM Channels WHERE owner='" + mUser.GetUserName() + "'");
    mUserSocket->waitForReadyRead(1000); // необходимо сделать задержку между двумя write'ами. 1-й write в методе ConnectToDB
    mUserSocket->write((Controller ? "0" : "1"));
    if (Controller) mUser.SetAvailChan(false);
    mDatabase->close();
}

void Worker::ConnectToChan()
{

}

void Worker::ChangePassword_User()
{
    ConnectToDB();
    // принимаем данные от клиента
    QByteArray Block = GetData();
    QString _oldPass = Block.split(';')[0];
    QString _newPass = Block.split(';')[1];    

    // проверка старого пароля
    Query.exec("SELECT username, password FROM Clients WHERE username='" + mUser.GetUserName() + "'");
    Query.last();
    if (_oldPass != Query.value(1)) {
        qDebug() << _oldPass << '\t' << Query.value(1).toString() <<'\n';
        mUserSocket->write("OLD PASSWORD IS WRONG");
        return;
    }

    mUserSocket->write("1");
    // меняем пароль на новый
    Query.exec("UPDATE Clients SET password='" + _newPass + "' WHERE username='" + mUser.GetUserName() + "'");
    mDatabase->close();
}

void Worker::ChangeName_User()
{
    ConnectToDB();
    // принимаем данные от клиента
    QByteArray Block = GetData();

    // Ищем совпадение имени в БД
    bool ControlPassed = true;
    Query.exec("SELECT username FROM Clients WHERE username='" + Block + "'");
    if (Query.next()) ControlPassed = false;

    // отправляем ответ клиенту
    if (ControlPassed) {
        QString _lastUsername = mUser.GetUserName(); // сохраняем старое имя для поиска по бд. оно - primary ky
        mUser.SetUsername(Block);
        Query.exec("UPDATE Clients SET username='" + Block + "' WHERE username='" + _lastUsername + "'");
        Query.exec("UPDATE Channels SET owner='" + Block + "' WHERE owner='" + _lastUsername + "'");
        mUserSocket->write("1");
    }
    else mUserSocket->write("0");
    mDatabase->close();
}


void Worker::Registration()
{
    ConnectToDB();
    // принимаем данные от клиента
    QByteArray Block = GetData();
    QString _Username = Block.split(';')[0];
    QString _Password = Block.split(';')[1];

    // проверка уникальности ника в БД
    Query.exec("SELECT username,password,avchan FROM Clients WHERE username='" + _Username + "'");
    bool ControlPassed = true;
    if (Query.next()) ControlPassed = false;

    // отправляем клиенту результат регистрации
    if (ControlPassed) {
        Query.exec("INSERT INTO Clients VALUES('" + _Username + "', '" + _Password + "', 0)");
        mUser.SetUsername(_Username);
        mUser.SetAvailChan(Query.value(2).toBool());
        mUser.PrintDataUser();
        mUserSocket->write("0");
    }
    else mUserSocket->write("ERROR REGISTRATION\nTRY AGAIN");
    mDatabase->close();
}


void Worker::Authorized()
{
    ConnectToDB();
    // принимаем данные от клиента
    QByteArray Block = GetData();
    QString _Username = Block.split(';')[0];
    QString _Password = Block.split(';')[1];

    // проверка данных в БД
    Query.exec("SELECT username,password,avchan FROM Clients WHERE username='" + _Username + "' AND password='" + _Password + "'");
    bool ControlPassed = false;
    if (Query.next()) ControlPassed = true;

    // отправляем клиенту результат входа и закрываем соединение с БД
    if (ControlPassed) {
        mUser.SetUsername(_Username);
        mUser.SetAvailChan(Query.value(2).toBool());
        mUser.PrintDataUser();
        // в случае успеха пароль и имя, отправленные клиентов, уже есть на клиентской стороне
        // поэтому отправим только состояние наличия канала у юзера
        mUserSocket->write((mUser.GetAvailChan() ? "1" : "0"));
    }
    else mUserSocket->write("ERROR AUTHORIZED");
    mDatabase->close();
}
