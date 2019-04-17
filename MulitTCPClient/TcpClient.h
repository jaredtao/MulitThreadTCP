#pragma once
#include <QObject>
#include <QTcpSocket>
class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    ~TcpClient();
    void timerEvent(QTimerEvent *event) override;
signals:

public slots:

private:
    QList<QTcpSocket *> m_socketList;
};

