#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQmlApplicationEngine>

#include "client.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    FriendListModel model;
    model.addFriend("2134", "324", "234");

    TCPClient *pClient = new TCPClient();
    pClient->connectToHost("192.168.0.108", 6000);

    engine.rootContext()->setContextProperty("client", pClient);
    engine.rootContext()->setContextProperty("friendListModel", &model);

    return app.exec();
}
