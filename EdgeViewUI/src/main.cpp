#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include "EdgeView.hpp"
#include "Controller.hpp"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(EdgeViewUI);

    const QUrl urlMain("qrc:///qml/MainWindow.qml");

    EdgeViewApplication  app(argc, argv);

    Controller controller(&app);

    QQmlApplicationEngine engine;

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []()
        { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("applicationData", &controller);
    engine.load(urlMain);
    
    controller.Initialize();

    return app.exec();
}
