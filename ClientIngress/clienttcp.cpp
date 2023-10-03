#include "clienttcp.h"
#include <QDebug>
#include <QTimer>
#include <QThread>

ClientTCP::ClientTCP(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &ClientTCP::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &ClientTCP::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &ClientTCP::receiveMessage);

    QTimer *messageTimer = new QTimer(this);
    connect(messageTimer, &QTimer::timeout, this, &ClientTCP::sendTwoMessages);
    messageTimer->start(1000); // Dispara a cada 1 segundo
}

void ClientTCP::connectToServer(const QString &ip, int port) {
    qDebug() << "ClientTCP::connectToServer";
    socket->connectToHost(ip, port);

    if (socket->waitForConnected()) {
        qDebug() << "Connected to server successfully";
        emit connectedToServer();
    } else {
        qDebug() << "Connection to server failed";
        emit connectionFailed();
    }
}

void ClientTCP::onConnected() {
    qDebug() << "Connected to server.";
}

void ClientTCP::onDisconnected() {
    qDebug() << "Disconnected from server.";
}

void ClientTCP::receiveMessage() {
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);

    emit messageReceived(message);

   // qDebug() << "Received message:" << message;
}

void ClientTCP::sendMessage(const QString &message) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray data = message.toUtf8();
        if (socket->write(data) != -1) {
            //qDebug() << "Message sent successfully:" << message;
            socket->flush();
        } else {
            qDebug() << "Failed to send message:" << message;
        }
    } else {
        //qDebug() << "Socket is not in connected state. Cannot send message:" << message;
    }
}

void ClientTCP::sendTwoMessages() {
    sendMessage("Primeira mensagem");

    // Espere um curto período de tempo (opcional)
    QThread::msleep(100);

    sendMessage("Segunda mensagem");
}
