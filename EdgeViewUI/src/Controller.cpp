#include "Controller.hpp"

Controller::Controller(QGuiApplication *appPtr, QObject *parent)
{
    controllerInstance = this;
    app = appPtr;
    traceString_ = "";
    scanLog_ = "";

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

    menuItemList_.append(ApplicationMenu(true, "Home", "Home.qml", "../images/Home.png"));
    menuItemList_.append(ApplicationMenu(true, "Enterprises", "Enterprises.qml", "../images/Enterprises.png"));
    menuItemList_.append(ApplicationMenu(true, "Sites", "Sites.qml", "../images/Sites.png"));
    menuItemList_.append(ApplicationMenu(true, "Areas", "Areas.qml", "../images/Areas.png"));
    menuItemList_.append(ApplicationMenu(true, "Devices", "Devices.qml", "../images/Devices.png"));
    menuItemList_.append(ApplicationMenu(true, "Assets", "Assets.qml", "../images/Assets.png"));
    menuItemList_.append(ApplicationMenu(true, "Rules", "Rules.qml", "../images/Rules.png"));
    menuItemList_.append(ApplicationMenu(true, "Roles", "Roles.qml", "../images/Roles.png"));
    menuItemList_.append(ApplicationMenu(true, "Users", "Users.qml", "../images/Users.png"));
    menuItemList_.append(ApplicationMenu(true, "Telemetry", "Telemetry.qml", "../images/Telemetry.png"));
    menuItemList_.append(ApplicationMenu(true, "Alarms", "Alarms.qml", "../images/Alarms.png"));

    currentDeviceAddress_ = "Sites : Update";
}

void Controller::Initialize()
{
    emit IsDarkThemeChanged();
    emit IsTraceEnabledChanged();
    emit ThemeChanged();
    emit MenuChanged();
    emit CurrentDeviceAddressChanged();
}

void Controller::setCurrentDeviceAddress(QString dev_addr)
{
    currentDeviceAddress_ = dev_addr;
    emit CurrentDeviceAddressChanged();
}

QString Controller::getCurrentDeviceAddress()
{
    return currentDeviceAddress_;
}

void Controller::setDeviceList(QList<Device> devlist)
{
    deviceList_.clear();

    foreach (Device mtr, devlist)
    {
        deviceList_.append(mtr);
    }

    emit DeviceListChanged();
}

QList<Device> Controller::getDeviceList()
{
    return deviceList_;
}

void Controller::invokeCancel()
{
}

void Controller::invokeExit()
{
    lastPage_ = "";
    exit(0);
}
