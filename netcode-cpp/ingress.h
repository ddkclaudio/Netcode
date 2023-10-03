#ifndef INGRESS_H
#define INGRESS_H

#include <QObject>
#include "ServerTCP.h"

class Ingress : public QObject
{
    Q_OBJECT
public:
    explicit Ingress(QObject *parent = nullptr);
    ~Ingress();
    void start();

private:
    ServerTCP *m_tcp;
};

#endif // INGRESS_H
