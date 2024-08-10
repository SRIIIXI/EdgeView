#include "Asset.hpp"

Asset::Asset()
{

}

Asset::Asset(QString iDeviceName, QString iSerialNo, QString iHardwareId, QString iType, QString iStatus)
{
    DeviceName_ = iDeviceName;
    SerialNo_ = iSerialNo;
    HardwareId_ = iHardwareId;
    Type_ = iType;
    Status_ = iStatus;
}

Asset::Asset(const Asset& other)
{
    DeviceName_ = other.DeviceName_;
    SerialNo_ = other.SerialNo_;
    HardwareId_ = other.HardwareId_;
    Type_ = other.Type_;
    Status_ = other.Status_;
}

Asset& Asset::operator = (const Asset& other)
{
    DeviceName_ = other.DeviceName_;
    SerialNo_ = other.SerialNo_;
    HardwareId_ = other.HardwareId_;
    Type_ = other.Type_;
    Status_ = other.Status_;
    return *this;
}

Asset::~Asset()
{

}
