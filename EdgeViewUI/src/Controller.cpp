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

    menuItemList_.append(ApplicationMenu(true, "Home", "Enterprises.qml", "../images/Home.png"));
    menuItemList_.append(ApplicationMenu(true, "Enterprises", "Enterprises.qml", "../images/Enterprise.png"));
    menuItemList_.append(ApplicationMenu(true, "Sites", "Sites.qml", "../images/Site.png"));
    menuItemList_.append(ApplicationMenu(true, "Areas", "Sites.qml", "../images/Area.png"));
    menuItemList_.append(ApplicationMenu(true, "Devices", "Devices.qml", "../images/Device.png"));
    menuItemList_.append(ApplicationMenu(true, "Assets", "Devices.qml", "../images/Asset.png"));
    menuItemList_.append(ApplicationMenu(true, "Rules", "Devices.qml", "../images/Rule.png"));
    menuItemList_.append(ApplicationMenu(true, "Users", "Devices.qml", "../images/User.png"));
    menuItemList_.append(ApplicationMenu(true, "Roles", "Devices.qml", "../images/Role.png"));
    menuItemList_.append(ApplicationMenu(true, "Telemetry", "Devices.qml", "../images/Telemetry.png"));
    menuItemList_.append(ApplicationMenu(true, "Alarms", "Devices.qml", "../images/Alarm.png"));

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
