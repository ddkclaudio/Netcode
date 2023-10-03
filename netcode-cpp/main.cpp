#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include "ingress.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Main thread ID:" << QThread::currentThreadId();

    Ingress *ingress = new Ingress();
    ingress->start();

    int ret = a.exec();

    delete ingress;

    return ret;
}
