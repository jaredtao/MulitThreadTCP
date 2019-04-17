#pragma once

#include <QObject>
#include <QList>
#include <Tcp.h>
class TCPManager : public QObject
{
    Q_OBJECT
public:
    explicit TCPManager(QObject *parent = nullptr);
    ~TCPManager();
signals:
    void infoReady(const QString &info);
public slots:
    void start();
    void stop();
private:
    QList<Tcp *> m_tcpList;
};

