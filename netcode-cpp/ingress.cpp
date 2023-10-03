#include "Ingress.h"

Ingress::Ingress(QObject *parent)
    : QObject(parent)
{
    m_tcp = new ServerTCP(this);
}

Ingress::~Ingress()
{
    delete m_tcp;
}

void Ingress::start()
{
    m_tcp->startServer(8080);
}
