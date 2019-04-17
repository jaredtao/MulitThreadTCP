#include "TcpClient.h"
#include <QHostAddress>
static const int sTcpCount = 8;
static const int sStartPort = 45450;

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    for (int i = 0; i< sTcpCount; ++i)
    {
        QTcpSocket *socket = new QTcpSocket;
        socket->connectToHost(QHostAddress::LocalHost, static_cast<quint16>(sStartPort + i));
        m_socketList.push_back(socket);
    }
    startTimer(100);
}

TcpClient::~TcpClient()
{
    qDeleteAll(m_socketList);
    m_socketList.clear();
}

void TcpClient::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    static int index = 0;
    QString info = QString(" info from %1").arg(sStartPort + index);
    m_socketList.at(index)->write(info.toUtf8());
    m_socketList.at(index)->flush();
    index++;
    if (index >= sTcpCount)
    {
        index = 0;
    }
}
