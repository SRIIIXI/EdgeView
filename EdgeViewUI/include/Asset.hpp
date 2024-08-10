#ifndef ASSET_
#define ASSET_

#include <QtCore>

class Asset
{
public:
    Q_GADGET

public:
    QString DeviceName_;
public:
    QString SerialNo_;
public:
    QString  HardwareId_;
public:
    QString  Type_;
public:
    QString  Status_;
public:
    Q_PROPERTY(QString DeviceName MEMBER DeviceName_)
    Q_PROPERTY(QString SerialNo MEMBER SerialNo_)
    Q_PROPERTY(QString HardwareId MEMBER HardwareId_)
    Q_PROPERTY(QString Type MEMBER Type_)
    Q_PROPERTY(QString Status MEMBER Status_)

public:
    Asset();
    Asset(QString iDeviceName, QString iSerialNo, QString  iHardwareId, QString  iType, QString  iStatus);
    Asset(const Asset& other);
    Asset& operator = (const Asset& other);
    ~Asset();
};


#endif