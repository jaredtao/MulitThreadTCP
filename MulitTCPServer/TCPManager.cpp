#include "TCPManager.h"

static const int sTcpCount = 8;
static const int sStartPort = 45450;

TCPManager::TCPManager(QObject *parent) : QObject(parent)
{}

TCPManager::~TCPManager()
{
    qDeleteAll(m_tcpList);
    m_tcpList.clear();
}
void TCPManager::start()
{
    m_tcpList.reserve(sTcpCount);
    for (int i = 0; i < sTcpCount; ++i)
    {
        Tcp *tcp = new Tcp;
        tcp->start(sStartPort + i);
        connect(tcp, &Tcp::infoReady, this, &TCPManager::infoReady);
        m_tcpList.append(tcp);
    }
}

void TCPManager::stop()
{
    for (int i = 0; i < m_tcpList.size(); ++i)
    {
        m_tcpList.at(i)->stop();
    }
}
