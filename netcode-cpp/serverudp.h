#ifndef SERVERUDP_H
#define SERVERUDP_H

#include <QObject>

class ServerUDP : public QObject
{
    Q_OBJECT
public:
    explicit ServerUDP(QObject *parent = nullptr);

signals:
};

#endif // SERVERUDP_H
