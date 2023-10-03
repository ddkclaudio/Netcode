#include "connectionhandler.h"
#include "statistics.h"
#include <QThread>

ConnectionHandler::ConnectionHandler(QTcpSocket *socket, QObject *parent)
    : QObject(parent), m_socket(socket)
{
    connect(m_socket, &QTcpSocket::readyRead, this, &ConnectionHandler::onDataReceived);
}

void ConnectionHandler::handleData()
{
    // Enquanto houver dados, leia e processe
    onDataReceived();
}

void ConnectionHandler::onDataReceived()
{
    QString clientId = QString("%1-%2").arg(m_socket->socketDescriptor()).arg(reinterpret_cast<quintptr>(QThread::currentThreadId()));

    QByteArray data = m_socket->readAll();
    qDebug() << "Received data:" << data << "on thread:" << QThread::currentThreadId() << " clientId: " << clientId;

    Statistics::update(clientId);

    m_socket->write(data);
}
