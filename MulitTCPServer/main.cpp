#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "TCPManager.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    TCPManager tcpMgr;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("tcpMgr", &tcpMgr);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
