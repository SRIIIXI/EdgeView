#include "Application.hpp"

Application::Application()
{

}

Application::Application(QString iDeviceName, QString iSerialNo, QString iHardwareId, QString iType, QString iStatus)
{
    DeviceName_ = iDeviceName;
    SerialNo_ = iSerialNo;
    HardwareId_ = iHardwareId;
    Type_ = iType;
    Status_ = iStatus;
}

Application::Application(const Application& other)
{
    DeviceName_ = other.DeviceName_;
    SerialNo_ = other.SerialNo_;
    HardwareId_ = other.HardwareId_;
    Type_ = other.Type_;
    Status_ = other.Status_;
}

Application& Application::operator = (const Application& other)
{
    DeviceName_ = other.DeviceName_;
    SerialNo_ = other.SerialNo_;
    HardwareId_ = other.HardwareId_;
    Type_ = other.Type_;
    Status_ = other.Status_;
    return *this;
}

Application::~Application()
{

}
