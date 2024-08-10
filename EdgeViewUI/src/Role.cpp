#include "Role.hpp"

Role::Role()
{

}

Role::Role(QString iDeviceName, QString iSerialNo, QString iHardwareId, QString iType, QString iStatus)
{
    DeviceName_ = iDeviceName;
    SerialNo_ = iSerialNo;
    HardwareId_ = iHardwareId;
    Type_ = iType;
    Status_ = iStatus;
}

Role::Role(const Role& other)
{
    DeviceName_ = other.DeviceName_;
    SerialNo_ = other.SerialNo_;
    HardwareId_ = other.HardwareId_;
    Type_ = other.Type_;
    Status_ = other.Status_;
}

Role& Role::operator = (const Role& other)
{
    DeviceName_ = other.DeviceName_;
    SerialNo_ = other.SerialNo_;
    HardwareId_ = other.HardwareId_;
    Type_ = other.Type_;
    Status_ = other.Status_;
    return *this;
}

Role::~Role()
{

}
