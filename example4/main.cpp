#include  <QApplication>  
#include  <QtDBus>  
#include <QDebug>  
#include  "test_adaptor.h"  
#include  "test.h"  
  
int main(int argc,char *argv[])  
{  
    QApplication app(argc,argv);  
  
    Test *test = new Test();  
  
    new TestInterfaceAdaptor(test);  
    QDBusConnection conn = QDBusConnection::sessionBus();  
    conn.registerObject("/",test);  
    conn.registerService("com.asianux.btagent");  
  
    return app.exec();  
}  
