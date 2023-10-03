#ifndef SERVERTCP_H
#define SERVERTCP_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QMutex>
#include <QList>

class ServerTCP : public QObject
{
    Q_OBJECT
public:
    explicit ServerTCP(QObject *parent = nullptr);
    ~ServerTCP();

    void startServer(quint16 port);
    void stopServer();
    const QList<QTcpSocket *> &getClients() const;

signals:

public slots:

private slots:
    void onNewConnection();
    void onSendPing();

private:
    void addClient(QTcpSocket *client);
    void removeClient(QTcpSocket *client);

    QTcpServer *m_server;
    QTimer m_pingTimer;
    QList<QTcpSocket *> m_clients;
    QMutex m_clientsMutex;
};

#endif // SERVERTCP_H
