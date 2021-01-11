#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDBusInterface interface("com.brion.test", "/",
            "com.brion.interface");
    interface.call("setName", "Brion");
    QDBusReply<QString> reply = interface.call("name");
    if (reply.isValid()) {
        qDebug()<<"name = "<<reply.value();
    }

    interface.call("setName", "ASML");
    reply = interface.call("name");
    if (reply.isValid()) {
        qDebug()<<"name = "<<reply.value();
    }

    return a.exec();
}

