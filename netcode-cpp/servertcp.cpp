#include "servertcp.h"
#include "connectionhandler.h"
#include "statistics.h"
#include <QDebug>
#include <QThread>
#include <QLocale>
#include <QDateTime>

ServerTCP::ServerTCP(QObject *parent)
    : QObject(parent), m_server(new QTcpServer(this))
{
    connect(m_server, &QTcpServer::newConnection, this, &ServerTCP::onNewConnection);

    // Inicializando o timer para enviar pings
    connect(&m_pingTimer, &QTimer::timeout, this, &ServerTCP::onSendPing);
    m_pingTimer.start(2000); // 2 segundos
}

ServerTCP::~ServerTCP()
{
    stopServer();
}

void ServerTCP::startServer(quint16 port)
{
    if (!m_server->listen(QHostAddress::Any, port))
    {
        qWarning("Server could not start!");
    }
    else
    {
        qDebug("Server started on port %d", port);
    }
}

void ServerTCP::stopServer()
{
    m_server->close();
}

void ServerTCP::onNewConnection()
{
    while (m_server->hasPendingConnections())
    {
        QTcpSocket *socket = m_server->nextPendingConnection();
        socket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1024 * 1024 * 1024); // 1MB

        addClient(socket);

        connect(socket, &QTcpSocket::readyRead, this, [this, socket]()
                {
                    QByteArray data = socket->readAll();
                   // qDebug() << "Received message:" << data << "on thread:" << QThread::currentThreadId();
                    socket->write(data);  // echo the data back for now

                    Statistics::update(QString::number(socket->socketDescriptor()));
                });

        connect(socket, &QTcpSocket::disconnected, this, [this, socket]()
                {
                    removeClient(socket);
                    socket->deleteLater();
                });
    }
}


void ServerTCP::addClient(QTcpSocket *client)
{
    QMutexLocker locker(&m_clientsMutex);
    m_clients.append(client);
    qDebug() << "Client connected. Total clients:" << m_clients.size() << "(after insertion) on thread:" << QThread::currentThreadId();
}

void ServerTCP::removeClient(QTcpSocket *client)
{
    QMutexLocker locker(&m_clientsMutex);
    m_clients.removeOne(client);
    qDebug() << "Client disconnected. Total clients:" << m_clients.size() << "(after removal) on thread:" << QThread::currentThreadId();
}


const QList<QTcpSocket *> &ServerTCP::getClients() const
{
    return m_clients;
}

void ServerTCP::onSendPing()
{
    // MOSTRA ESTATISTICAS
    Statistics::show();

    // ENVIA DADOS PERIODICAMENTE
    QLocale brazil(QLocale::Portuguese, QLocale::Brazil);
    QString currentDateTime = brazil.toString(QDateTime::currentDateTime(), "dd/MM/yyyy HH:mm:ss");
    QString pingMessage = "Ping " + currentDateTime;

    QMutexLocker locker(&m_clientsMutex);
    for (QTcpSocket *client : m_clients)
    {
        client->write(pingMessage.toUtf8());
        //qDebug() << "Enviando: " << pingMessage.toUtf8();
    }
}
