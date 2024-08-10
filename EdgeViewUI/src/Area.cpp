#include "Area.hpp"

Area::Area()
{

}

Area::Area(QString iDeviceName, QString iSerialNo, QString iHardwareId, QString iType, QString iStatus)
{
    DeviceName_ = iDeviceName;
    SerialNo_ = iSerialNo;
    HardwareId_ = iHardwareId;
    Type_ = iType;
    Status_ = iStatus;
}

Area::Area(const Area& other)
{
    DeviceName_ = other.DeviceName_;
    SerialNo_ = other.SerialNo_;
    HardwareId_ = other.HardwareId_;
    Type_ = other.Type_;
    Status_ = other.Status_;
}

Area& Area::operator = (const Area& other)
{
    DeviceName_ = other.DeviceName_;
    SerialNo_ = other.SerialNo_;
    HardwareId_ = other.HardwareId_;
    Type_ = other.Type_;
    Status_ = other.Status_;
    return *this;
}

Area::~Area()
{

}
