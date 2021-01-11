#ifndef  TEST_H  
#define  TEST_H  

#include  <QtCore>  
#include  <QTimer>  
#include  <QDebug>  

class Person : public QObject  
{  
    Q_OBJECT  

    Q_CLASSINFO("D-Bus Interface", "com.brion.interface")

    signals:
    void nameChanged(QString);
    void ageChanged(int);

    public slots:
        QString name() const { return m_name; }
    // can't be reference

    void setName(QString name) {
        qDebug() << "server setName:" << name;
        m_name = name;
    }

    int age() const { return m_age; }
    void setAge(int age) {
        qDebug() << "server setAge:" << age;
        m_age = age;
    }

    public:  
    Person();  

    private:
    QString m_name;
    int m_age;

}; 

#endif  /*TEST_H*/  
