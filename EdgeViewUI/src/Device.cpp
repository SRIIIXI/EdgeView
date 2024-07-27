#include "Device.hpp"

Device::Device()
{

}

Device::Device(QString iDeviceName, QString iSerialNo, QString iHardwareId, QString iStatus)
{
    DeviceName_ = iDeviceName;
    SerialNo_ = iSerialNo;
    HardwareId_ = iStatus;
    Status_ = iHardwareId;
}

Device::Device(const Device& other)
{
    DeviceName_ = other.DeviceName_;
    SerialNo_ = other.SerialNo_;
    HardwareId_ = other.HardwareId_;
    Status_ = other.Status_;
}

Device& Device::operator = (const Device& other)
{
    DeviceName_ = other.DeviceName_;
    SerialNo_ = other.SerialNo_;
    HardwareId_ = other.HardwareId_;
    Status_ = other.Status_;
    return *this;
}

Device::~Device()
{

}
