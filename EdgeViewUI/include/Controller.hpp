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

#include "Enterprise.hpp"
#include "Site.hpp"
#include "Area.hpp"
#include "Device.hpp"
#include "Asset.hpp"
#include "Rule.hpp"
#include "Role.hpp"
#include "User.hpp"
#include "EdgeApplication.hpp"
#include "Telemetry.hpp"
#include "Alarm.hpp"
#include "Configuration.hpp"
#include "About.hpp"

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

    Q_PROPERTY(QList<Enterprise> EnterpriseList READ getEnterpriseList NOTIFY EnterpriseListChanged);
    QList<Enterprise> getEnterpriseList();

    Q_PROPERTY(QList<Site> SiteList READ getSiteList NOTIFY SiteListChanged);
    QList<Site> getSiteList();

    Q_PROPERTY(QList<Area> AreaList READ getAreaList NOTIFY AreaListChanged);
    QList<Area> getAreaList();

    Q_PROPERTY(QList<Device> DeviceList READ getDeviceList NOTIFY DeviceListChanged);
    QList<Device> getDeviceList();

    Q_PROPERTY(QList<Asset> AssetList READ getAssetList NOTIFY AssetListChanged);
    QList<Asset> getAssetList();

    Q_PROPERTY(QList<Rule> RuleList READ getRuleList NOTIFY RuleListChanged);
    QList<Rule> getRuleList();

    Q_PROPERTY(QList<Role> RoleList READ getRoleList NOTIFY RoleListChanged);
    QList<Role> getRoleList();

    Q_PROPERTY(QList<User> UserList READ getUserList NOTIFY UserListChanged);
    QList<User> getUserList();

    Q_PROPERTY(QList<EdgeApplication> EdgeApplicationList READ getEdgeApplicationList NOTIFY EdgeApplicationListChanged);
    QList<EdgeApplication> getEdgeApplicationList();

    Q_PROPERTY(QList<Telemetry> TelemetryList READ getTelemetryList NOTIFY TelemetryListChanged);
    QList<Telemetry> getTelemetryList();

    Q_PROPERTY(QList<Alarm> AlarmList READ getAlarmList NOTIFY AlarmListChanged);
    QList<Alarm> getAlarmList();

    Q_PROPERTY(Configuration ApplicationConfiguration READ getApplicationConfiguration NOTIFY ApplicationConfigurationChanged);
    Configuration getApplicationConfiguration();

    Q_PROPERTY(About ApplicationAbout READ getApplicationAbout NOTIFY ApplicationAboutChanged);
    About getApplicationAbout();

    void Initialize();

signals:
    void ThemeChanged();
    void MenuChanged();
    void IsDarkThemeChanged();

    //UI events and operations states
    void menuAction();
    void pageAction(int ipage);

    //Domain objects
    void EnterpriseListChanged();
    void enterpriseAction();

    void SiteListChanged();
    void siteAction();

    void AreaListChanged();
    void areaAction();

    void DeviceListChanged();
    void deviceAction();

    void AssetListChanged();
    void assetAction();

    void RuleListChanged();
    void ruleAction();

    void RoleListChanged();
    void roleAction();

    void UserListChanged();
    void userAction();

    void EdgeApplicationListChanged();
    void edgeApplicationAction();

    void TelemetryListChanged();
    void telemetryAction();

    void AlarmListChanged();
    void alarmAction();

    void ApplicationConfigurationChanged();
    void applicationConfigurationAction();

    void ApplicationAboutChanged();
    void applicationAboutAction();

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

    //Domain object lists
    QList<Enterprise> enterpriseList_;
    QList<Site> siteList_;
    QList<Area> areaList_;
    QList<Device> deviceList_;
    QList<Asset> assetList_;
    QList<Rule> ruleList_;
    QList<Role> roleList_;
    QList<User> userList_;
    QList<EdgeApplication> edgeApplicationList_;
    QList<Telemetry> telemetryList_;
    QList<Alarm> alarmList_;
    Configuration applicationConfiguration_;
    About applicationAbout_;
};

extern Controller* controllerInstance;

#endif
