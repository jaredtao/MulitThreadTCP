#include "Tcp.h"

void TcpWorker::onStart(int port)
{
    m_port = port;
    m_server = std::make_unique<QTcpServer>();
    connect(m_server.get(), &QTcpServer::newConnection, this, &TcpWorker::onNewConnection);
    m_server->listen(QHostAddress::LocalHost, static_cast<quint16>(port));
    qWarning() << QThread::currentThreadId() <<  "listen " << port;
}

void TcpWorker::onStop()
{
    m_server->close();

}

void TcpWorker::onNewConnection()
{
    QTcpSocket *socket = m_server->nextPendingConnection();

    if (socket)
    {
        emit infoReady(QString("%1: new connection").arg(m_port));
        connect(socket, &QTcpSocket::readyRead, this, &TcpWorker::onReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &TcpWorker::onDisconnected);
    }
}

void TcpWorker::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket)
    {
        auto data = socket->readAll();
        emit infoReady(QString("%1:").arg(m_port) + QString(data));
    }
}

void TcpWorker::onDisconnected()
{
    emit infoReady(QString("%1: disconnect").arg(m_port));
}


Tcp::Tcp(QObject *parent) : QObject(parent)
{
    m_worker = new TcpWorker;
    m_worker->moveToThread(&m_thread);
    connect(this,  &Tcp::start, m_worker, &TcpWorker::onStart);
    connect(this,  &Tcp::stop, m_worker, &TcpWorker::onStop);
    connect(m_worker, &TcpWorker::infoReady, this, &Tcp::infoReady);
    connect(&m_thread, &QThread::finished, m_worker, &TcpWorker::deleteLater);
    m_thread.start();
}

Tcp::~Tcp()
{
    if (m_thread.isRunning())
    {
        emit stop();
        m_thread.quit();
        m_thread.wait();
    }
}


