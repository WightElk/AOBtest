//
// 1. UI and code itself can be improved.
// 2. There are almost no comments, I tried to make it faster.
// VG
//

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "model.h"
#include "loader.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    const QString jsonUrl = QStringLiteral("https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/data.json");
    Model model;
    Loader loader;
    loader.load(jsonUrl, model);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                        if (!obj && url == objUrl)
                            QCoreApplication::exit(-1);
                    }, Qt::QueuedConnection);

    QQmlContext *context = engine.rootContext();
    context->setContextProperty(QStringLiteral("jsonModel"), QVariant::fromValue(&model));

    engine.load(url);

    return app.exec();
}
