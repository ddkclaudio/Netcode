#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <QObject>
#include <QTcpSocket>

class QTimer; // Adicione esta linha

class ClientTCP : public QObject
{
    Q_OBJECT
public:
    explicit ClientTCP(QObject *parent = nullptr);
    void connectToServer(const QString &ip, int port);
    void sendMessage(const QString &message);

signals:
    void messageReceived(const QString &message);
    void connectedToServer();
    void connectionFailed();

public slots:
    void receiveMessage();
    void onConnected();
    void onDisconnected();
    void sendTwoMessages(); // Adicione esta linha

private:
    QTcpSocket *socket;
};

#endif // CLIENTTCP_H
