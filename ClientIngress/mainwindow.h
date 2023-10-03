#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

namespace Ui
{
    class MainWindow;
}

class ClientTCP;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startTCPConnections();
    void sendTCPMessage();

private:
    Ui::MainWindow *ui;
    QList<ClientTCP *> clients; // Lista de clientes TCP
};

#endif // MAINWINDOW_H
