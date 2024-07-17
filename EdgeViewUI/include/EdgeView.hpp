#ifndef EDGE_VIEW
#define EDGE_VIEW

#include <QtQuickWidgets/QQuickWidget>
#include <QGuiApplication>
#include <QPalette>
#include <QMap>
#include <QObject>
#include <QString>
#include <QQuickItem>
#include <QSettings>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickView>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDir>
#include <QFile>

class EdgeViewApplication : public QGuiApplication
{
    Q_OBJECT
public:
    explicit EdgeViewApplication(int argc, char *argv[]);
    virtual ~EdgeViewApplication();
private:
};

extern EdgeViewApplication* edgeViewPtr;

#endif
