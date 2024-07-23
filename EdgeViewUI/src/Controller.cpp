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
}

void Controller::Initialize()
{
    emit IsDarkThemeChanged();
    emit ThemeChanged();
    emit MenuChanged();
}

void Controller::invokeCancel()
{
}

void Controller::invokeExit()
{
    lastPage_ = "";
    exit(0);
}
