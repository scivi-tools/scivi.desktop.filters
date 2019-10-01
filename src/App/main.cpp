#include <QPluginLoader>
#include <QDebug>
#include <QDir>
#include <QList>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QApplication>
#include <QJsonObject>
#include <QDateTime>
#include <QColor>
#include <QtQuick/QQuickItem>
#include <exception>

#include <filterimplementation.h>
#include <filterfactory.h>
#include <sinkfilter.h>

using namespace scivi::filters;

#define WEBSOCKET_GLOVE

static QList<FilterPtr> implementations;

static const auto findFilter = [](QString filterName) {
    auto filter = std::find_if(implementations.begin(), implementations.end(), [filterName](FilterPtr f) {
        return f->getName() == filterName;
    });
    return filter == implementations.end() ? nullptr : *filter;
};

void chartExample(SinkFilter *scene) {
    auto const &verticalStack = findFilter("VerticalStack");
    auto const &linear = findFilter("LinearDatetime");
    auto const &area = findFilter("AreaDatetime");
    auto const &fileInput = findFilter("InputFile");

    (*fileInput)["path"] = "../../Client/Data/temp_data.txt";
    (*linear)["color"] = QColor(Qt::red);
    (*linear)["xtitle"] = "Time";
    (*area)["color"] = QColor(Qt::green);
    (*area)["xtitle"] = "Time";
    QObject::connect(fileInput, &FilterImplementation::produced, linear, &FilterImplementation::consume);
    QObject::connect(fileInput, &FilterImplementation::produced, area, &FilterImplementation::consume);
    QObject::connect(linear, &FilterImplementation::produced, verticalStack, [=](QVariant data, const QString& slotName) {
        if (slotName == "visual") {
            verticalStack->consume(data, "visual1");
        }
    });
    QObject::connect(area, &FilterImplementation::produced, verticalStack, [=](QVariant data, const QString& slotName) {
        if (slotName == "visual") {
            verticalStack->consume(data, "visual2");
        }
    });
    QObject::connect(verticalStack, &FilterImplementation::produced, scene, &FilterImplementation::consume);
}

void surfaceExample(SinkFilter *scene) {
    auto const &gridInputFile = findFilter("GridInputFile");
    auto const &smoothSurface = findFilter("SmoothSurface");
    auto const &surface3D = findFilter("Surface3D");

    (*gridInputFile)["path"] = "../../Client/Data/surface.txt";
    (*smoothSurface)["c"] = 2.0;
    (*smoothSurface)["resolution"] = 17.0;
    QObject::connect(gridInputFile, &FilterImplementation::produced, smoothSurface, &FilterImplementation::consume);
    QObject::connect(smoothSurface, &FilterImplementation::produced, surface3D, &FilterImplementation::consume);
    QObject::connect(surface3D, &FilterImplementation::produced, scene, &FilterImplementation::consume);
}

void cursorActuatorExample(SinkFilter *scene) {
    auto const &webSocketInput = findFilter("WebSocketInput");
    auto const &cursorActuator = findFilter("CursorActuator");

    (*webSocketInput)["url"] = "ws://localhost:8998";
    QObject::connect(webSocketInput, &FilterImplementation::produced, [cursorActuator](QVariant data) {
        QVariantList list = data.toList();
        int x = list[0].toInt();
        int y = list[1].toInt();
        cursorActuator->consume(x, "x");
        cursorActuator->consume(y, "y");
    });
}

void websocketTemperatureExample(SinkFilter *scene) {
    auto const &webSocketInput = findFilter("WebSocketInput");
    auto const &linear = findFilter("LinearDatetime");
    auto const &timeSeriesAdapter = findFilter("TimeSeriesAdapter");

    (*webSocketInput)["url"] = "ws://localhost:8999";
    (*linear)["color"] = QColor(Qt::red);
    (*linear)["xtitle"] = "Time";
    QObject::connect(webSocketInput, &FilterImplementation::produced, timeSeriesAdapter, &FilterImplementation::consume);
    QObject::connect(timeSeriesAdapter, &FilterImplementation::produced, linear, &FilterImplementation::consume);
    QObject::connect(linear, &FilterImplementation::produced, scene, &FilterImplementation::consume);
}

void websocketGaugeExample(SinkFilter *scene) {
    auto const &webSocketInput = findFilter("WebSocketInput");
    auto const &gauge = findFilter("Gauge");
    auto const &floatAdapter = findFilter("FloatAdapter");

    (*webSocketInput)["url"] = "ws://localhost:8998";
    (*gauge)["min"] = -50;
    (*gauge)["max"] = 50;
    (*gauge)["color"] = QColor(Qt::red);
    QObject::connect(webSocketInput, &FilterImplementation::produced, floatAdapter, &FilterImplementation::consume);
    QObject::connect(floatAdapter, &FilterImplementation::produced, gauge, &FilterImplementation::consume);
    QObject::connect(gauge, &FilterImplementation::produced, scene, &FilterImplementation::consume);
}

auto inline connectfilters(FilterImplementation *producer, FilterImplementation *consumer, const QString &output, const QString &input) {
    return QObject::connect(producer, &FilterImplementation::produced, [consumer, input, output](QVariant data, const QString &socketName) {
        if (socketName == output) {
            consumer->consume(data, input);
        }
    });
}

void websocketGloveExample(SinkFilter *scene) {
    Q_UNUSED(scene)
    auto const &glove = findFilter("Glove");
    auto const &orientation2Coord = findFilter("Orientation2Coord");
    auto const &mouse = findFilter("Mouse");
    if (!glove) {
        qFatal("Cannot find glove filter!");
    }
    if (!orientation2Coord) {
        qFatal("Cannot find orientation2coord filter!");
    }
    if (!mouse) {
        qFatal("Cannot find mouse filter!");
    }

    (*glove)["url"] = "ws://192.168.4.1:81/";
    QObject::connect(glove, &FilterImplementation::produced, [](QVariant data, const QString &socketName) {
        qDebug() << "Got from glove filter " << socketName << " : " << data;
    });
    QObject::connect(orientation2Coord, &FilterImplementation::produced, [](QVariant data, const QString &socketName) {
        qDebug() << "Got from orientation filter " << socketName << " : " << data;
    });
    connectfilters(glove, orientation2Coord, "Orientation", "Orientation");
    connectfilters(orientation2Coord, mouse, "Coord", "Coord");
    connectfilters(glove, mouse, "Finger", "Pressed");

    // To test that mouse filter works in hardcoded way
//    mouse->consume(QVariantList { 0, 0 }, "Coord");
//    mouse->consume(qVariantFromValue(true), "Pressed");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Application path is " << qApp->applicationDirPath();
    qDebug() << "Lib path is " << qApp->libraryPaths();
    QDir dir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
    dir.cdUp();
#endif
#if defined(Q_OS_MACOS)
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
#endif
    dir.cdUp();
    dir.cd("lib");

    implementations.clear();
    for (const auto &pluginDirName :
         dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QDir pluginDir(dir.absoluteFilePath(pluginDirName));
        for (const auto& filename : pluginDir.entryList(QDir::Files)) {
            QString path = pluginDir.absoluteFilePath(filename);
            QPluginLoader loader(path);
            auto *plugin = loader.instance();
            if (!QLibrary::isLibrary(path)) {
                qWarning() << "Provided plugin is not a library! at" << path;
                continue;
            }
            if (plugin) {
                auto factory = qobject_cast<FilterFactory*>(plugin);
                auto impl = factory->create(&a);
                implementations << impl;
                qInfo() << "Found plugin " << impl->getName() << " inside " << path;
                if (qobject_cast<SinkFilter*>(plugin) != nullptr) {
                    qDebug() << "Is sink filter";
                }
            } else {
                qWarning() << "Couldn't load plugin. Error: " << loader.errorString();
            }
        }
    }
    if (implementations.isEmpty()) {
        qDebug() << "Couldnt load filter implementations";
        return 0;
    }

    SinkFilter* scene = static_cast<SinkFilter*>(findFilter("Scene"));

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    QObject* rootObj = engine.rootObjects().first();
    auto myRect = rootObj->findChild<QQuickItem*>("myRect");
    scene->setContainer(myRect);

#ifdef CHART
    {
        chartExample(scene);
    }
#elif defined(SURFACE)
    {
        surfaceExample(scene);
    }
#elif defined(WEBSOCKET_CURSOR)
    {
        cursorActuatorExample(scene);
    }
#elif defined(WEBSOCKET_CHART)
    {
        websocketTemperatureExample(scene);
    }
#elif defined(WEBSOCKET_GAUGE)
    {
        websocketGaugeExample(scene);
    }
#elif defined(WEBSOCKET_GLOVE)
    {
        websocketGloveExample(scene);
    }
#endif
    for (const auto& impl: implementations) {
        impl->onStart();
    }

    return a.exec();
}
