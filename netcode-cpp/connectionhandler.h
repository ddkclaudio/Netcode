#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QObject>
#include <QTcpSocket>

class ConnectionHandler : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionHandler(QTcpSocket *socket, QObject *parent = nullptr);

public slots:
    void handleData();

signals:
    void finished();

private slots:
    void onDataReceived();

private:
    QTcpSocket *m_socket;
};

#endif // CONNECTIONHANDLER_H
