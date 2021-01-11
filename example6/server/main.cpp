#include <QtDBus/QDBusConnection>
#include <QApplication>
#include "person.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Person *person = new Person();  

    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    if (sessionBus.registerService("com.brion.service")) {
        sessionBus.registerObject("/",  person,
                //QDBusConnection::ExportAllContents);
            QDBusConnection::ExportNonScriptableSlots);
    }
    return a.exec();
}
