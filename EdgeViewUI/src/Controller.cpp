#include "Controller.hpp"

Controller::Controller(QGuiApplication *appPtr, QObject *parent)
{
    controllerInstance = this;
    app = appPtr;

    lastPage_ = "";
    isDarkTheme_ = true;

    if(app->palette().window().color().value() > app->palette().windowText().color().value())
    {
        isDarkTheme_ = false;
        theme_.EnableLightMode();
    }
    else
    {
        isDarkTheme_ = true;
        theme_.EnableDarkMode();
    }

    isDarkTheme_ = false;
    theme_.EnableLightMode();

    QImage appImg("../images/EdgeView.png");
    QIcon icn(QPixmap::fromImage(appImg));
    appPtr->setWindowIcon(icn);

    if(isDarkTheme_)
    {
        menuItemList_.append(ApplicationMenu(true, "Home", "Home.qml", "../images/HomeWhite.png", true));
        menuItemList_.append(ApplicationMenu(true, "Enterprises", "Enterprises.qml", "../images/EnterprisesWhite.png"));
        menuItemList_.append(ApplicationMenu(true, "Sites", "Sites.qml", "../images/SitesWhite.png"));
        menuItemList_.append(ApplicationMenu(true, "Areas", "Areas.qml", "../images/AreasWhite.png"));
        menuItemList_.append(ApplicationMenu(true, "Devices", "Devices.qml", "../images/DevicesWhite.png"));
        menuItemList_.append(ApplicationMenu(true, "Assets", "Assets.qml", "../images/AssetsWhite.png"));
        menuItemList_.append(ApplicationMenu(true, "Rules", "Rules.qml", "../images/RulesWhite.png"));
        menuItemList_.append(ApplicationMenu(true, "Roles", "Roles.qml", "../images/RolesWhite.png"));
        menuItemList_.append(ApplicationMenu(true, "Users", "Users.qml", "../images/UsersWhite.png"));
        menuItemList_.append(ApplicationMenu(true, "Telemetry", "Telemetry.qml", "../images/TelemetryWhite.png"));
        menuItemList_.append(ApplicationMenu(true, "Alarms", "Alarms.qml", "../images/AlarmsWhite.png"));
    }
    else
    {
        menuItemList_.append(ApplicationMenu(true, "Home", "Home.qml", "../images/HomeBlack.png", true));
        menuItemList_.append(ApplicationMenu(true, "Enterprises", "Enterprises.qml", "../images/EnterprisesBlack.png"));
        menuItemList_.append(ApplicationMenu(true, "Sites", "Sites.qml", "../images/SitesBlack.png"));
        menuItemList_.append(ApplicationMenu(true, "Areas", "Areas.qml", "../images/AreasBlack.png"));
        menuItemList_.append(ApplicationMenu(true, "Devices", "Devices.qml", "../images/DevicesBlack.png"));
        menuItemList_.append(ApplicationMenu(true, "Assets", "Assets.qml", "../images/AssetsBlack.png"));
        menuItemList_.append(ApplicationMenu(true, "Rules", "Rules.qml", "../images/RulesBlack.png"));
        menuItemList_.append(ApplicationMenu(true, "Roles", "Roles.qml", "../images/RolesBlack.png"));
        menuItemList_.append(ApplicationMenu(true, "Users", "Users.qml", "../images/UsersBlack.png"));
        menuItemList_.append(ApplicationMenu(true, "Telemetry", "Telemetry.qml", "../images/TelemetryBlack.png"));
        menuItemList_.append(ApplicationMenu(true, "Alarms", "Alarms.qml", "../images/AlarmsBlack.png"));

    }

    deviceList_.append(Device("Router", "1111111", "AAAAAA", "Gateway", "Active"));
    deviceList_.append(Device("Modem", "22222222", "BBBBBB", "Gateway", "Decommisioned"));
    deviceList_.append(Device("Sensor", "33333333", "CCCCCC", "Sensor", "InActive"));
    deviceList_.append(Device("Actuator", "44444444", "DDDDDD", "Actuator", "In Stock"));
}

void Controller::Initialize()
{
    emit IsDarkThemeChanged();
    emit ThemeChanged();
    emit MenuChanged();
    emit DeviceListChanged();
    emit deviceAction();
}

void Controller::invokeCancel()
{
}

void Controller::invokeExit()
{
    lastPage_ = "";
    exit(0);
}

QList<Device> Controller::getDeviceList()
{
    return deviceList_;
}
