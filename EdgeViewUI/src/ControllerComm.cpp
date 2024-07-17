#include "Controller.hpp"

Controller* controllerInstance = nullptr;

void Controller::invokeScan()
{
    deviceMap_.clear();
    ClearScanLog();
    emit progressIndicatorsOn();
}

void Controller::invokeConnectDevice(QString address)
{
    ClearTrace();

    Device mt;
    bool found = false;
    foreach(Device mtr , deviceList_)
    {
        if(mtr.DeviceAddress_ == address)
        {
            mt = mtr;
            currentDeviceAddress_ = address;
            found = true;
            break;
        }
    }

    if(found)
    {
        emit progressIndicatorsOn();
    }
    else
    {
        emit deviceMessage(false, "Device not found");
    }
}

void Controller::invokeDisconnectDevice(QString address)
{
    ClearTrace();
}
