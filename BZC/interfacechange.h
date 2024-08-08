#ifndef INTERFACECHAGE_H
#define INTERFACECHAGE_H

#include <QObject>
#include "cytglobaltype.h"
#include <QUdpSocket>

class InterfaceChange : public QObject
{
    Q_OBJECT
private:
    InterfaceChange();
    ~InterfaceChange();
public:
    static InterfaceChange * getInstance()
    {
        static InterfaceChange * inst = new InterfaceChange();
        return inst;
    }

    void change(ShowType st);

private:
    QUdpSocket * m_udp;
signals:

};

#endif // INTERFACECHAGE_H
