#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clienttcp.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tcpConnectButton, &QPushButton::clicked, this, &MainWindow::startTCPConnections);
    connect(ui->tcpSendButton, &QPushButton::clicked, this, &MainWindow::sendTCPMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTCPConnections()
{
    ui->tcpConnectButton->setEnabled(false);

    int numClients = ui->numberOfClientsSpinBox->value();
    QString ip = ui->serverIpLineEdit->text();
    int port = ui->serverPortLineEdit->text().toInt();

    for (int i = 0; i < numClients; i++)
    {
        ClientTCP *client = new ClientTCP(this);
        client->connectToServer(ip, port);
        // Armazene o cliente em uma lista se quiser gerenciá-los depois
        clients.append(client); // Adicione o cliente à lista
    }

    ui->tcpSendButton->setEnabled(true);
}

void MainWindow::sendTCPMessage()
{
    QString message = ui->tcpMessageLineEdit->text(); // Obtém a mensagem da interface

    // Itera pela lista de clientes e envia a mensagem para cada um
    for (ClientTCP *client : clients)
    {
        client->sendMessage(message);
    }
}
