#pragma once

#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <memory>
class TcpWorker : public QObject
{
    Q_OBJECT
public:

public slots:
    void onStart(int port);
    void onStop();
protected slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
signals:
    void infoReady(const QString &info);

private:
    std::unique_ptr<QTcpServer> m_server = nullptr;
    int m_port;
};
class Tcp : public QObject
{
    Q_OBJECT
public:
    explicit Tcp(QObject *parent = nullptr);
    ~Tcp();
signals:
    void start(int port);
    void stop();

    void infoReady(const QString &info);
public slots:

private:
    QThread m_thread;
    TcpWorker *m_worker;
};
