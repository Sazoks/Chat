#include <QCoreApplication>
#include <server.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server Server1(8080);
    return a.exec();
}
