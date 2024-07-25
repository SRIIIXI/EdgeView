#ifndef CONTROLLER_
#define CONTROLLER_

#include <QObject>
#include <QGuiApplication>
#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QList>
#include <QTimer>
#include <QUuid>
#include <QPalette>
#include <QIcon>

#include "ApplicationTheme.hpp"
#include "ApplicationMenu.hpp"

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QGuiApplication* appPtr, QObject *parent = nullptr);

    Q_INVOKABLE void invokeThemeUpdate();
    Q_INVOKABLE void invokeChangePage(int ipage);

    Q_INVOKABLE void invokeCancel();
    Q_INVOKABLE void invokeExit();

    Q_INVOKABLE void invokeSaveCurrentPage(QString page);
    Q_INVOKABLE QString invokeRetreiveLastPage();

    Q_PROPERTY (bool IsDarkTheme READ getIsDarkTheme WRITE setIsDarkTheme NOTIFY IsDarkThemeChanged)
    bool getIsDarkTheme();
    void setIsDarkTheme(bool isdarktheme);

    Q_PROPERTY (ApplicationTheme Theme READ getTheme NOTIFY ThemeChanged)
    ApplicationTheme getTheme();

    Q_PROPERTY (QList<ApplicationMenu> Menu READ getMenu NOTIFY MenuChanged)
    QList<ApplicationMenu> getMenu();

    void Initialize();

signals:
    void ThemeChanged();
    void MenuChanged();
    void IsDarkThemeChanged();

    //UI events and operations states
    void menuAction();
    void pageAction(int ipage);

    //Specifc errors

    //Trace/progress
    void initializationComplete();

    //UI Indicators
    void progressIndicatorsOff();
    void progressIndicatorsOn();

private slots:

private:
    QGuiApplication* app;

    //Object lists
    QList<ApplicationMenu> menuItemList_;

    //Globals / Miscellanous
    QString lastPage_;

    bool isDarkTheme_;
    ApplicationTheme theme_;
};

extern Controller* controllerInstance;

#endif
