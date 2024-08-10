#include "Rule.hpp"

Rule::Rule()
{

}

Rule::Rule(QString iDeviceName, QString iSerialNo, QString iHardwareId, QString iType, QString iStatus)
{
    DeviceName_ = iDeviceName;
    SerialNo_ = iSerialNo;
    HardwareId_ = iHardwareId;
    Type_ = iType;
    Status_ = iStatus;
}

Rule::Rule(const Rule& other)
{
    DeviceName_ = other.DeviceName_;
    SerialNo_ = other.SerialNo_;
    HardwareId_ = other.HardwareId_;
    Type_ = other.Type_;
    Status_ = other.Status_;
}

Rule& Rule::operator = (const Rule& other)
{
    DeviceName_ = other.DeviceName_;
    SerialNo_ = other.SerialNo_;
    HardwareId_ = other.HardwareId_;
    Type_ = other.Type_;
    Status_ = other.Status_;
    return *this;
}

Rule::~Rule()
{

}
