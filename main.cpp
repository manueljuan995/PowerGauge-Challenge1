#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "backend/backend.h"
#include "backend/datasource.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    qmlRegisterType<DataSource>("Challenge", 1, 0, "DataSource");

    context->setContextProperty("Backend", Backend::instance());

    QObject::connect(qApp, &QCoreApplication::aboutToQuit, [=](){
        Backend::deleteInstance();
    });

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(QUrl(QLatin1String("qrc:/ui/main.qml")));

    return app.exec();
}
