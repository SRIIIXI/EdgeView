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
}

void Controller::Initialize()
{
    emit IsDarkThemeChanged();
    emit IsTraceEnabledChanged();
    emit ThemeChanged();
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
