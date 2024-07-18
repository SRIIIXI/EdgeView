#ifndef CONTROLLER_
#define CONTROLLER_

#include <QObject>
#include <QGuiApplication>
#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QList>
#include <QTimer>
#include <QUuid>
#include <QPalette>

#include "ApplicationTheme.hpp"
#include "ApplicationMenu.hpp"

class Device
{
public:
    Q_GADGET

public:
    QString DeviceAddress_;
public:
    QString DeviceName_;
public:
    QString RSSI_;
public:
    QString Status_;
public:
    Q_PROPERTY(QString DeviceAddress MEMBER DeviceAddress_)
    Q_PROPERTY(QString DeviceName MEMBER DeviceName_)
    Q_PROPERTY(QString RSSI MEMBER RSSI_)
    Q_PROPERTY(QString Status MEMBER Status_)
public:
    ~Device()
    {
    }

    Device()
    {
        DeviceAddress_ = "";
        DeviceName_ = "";
        RSSI_ = "";
        Status_ = "0";
    }

    Device(QString iDevAddr, QString iDevName, QString iRSSI, QString iStatusStr)
    {
        DeviceAddress_ = iDevAddr;
        DeviceName_ = iDevName;
        RSSI_ = iRSSI;
        Status_ = iStatusStr;
    }

    Device(const Device& other)
    {
        DeviceAddress_ = other.DeviceAddress_;
        DeviceName_ = other.DeviceName_;
        RSSI_ = other.RSSI_;
        Status_ = other.Status_;
    }

    Device& operator = (const Device& other)
    {
        DeviceAddress_ = other.DeviceAddress_;
        DeviceName_ = other.DeviceName_;
        RSSI_ = other.RSSI_;
        Status_ = other.Status_;
        return *this;
    }
};

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QGuiApplication* appPtr, QObject *parent = nullptr);

    Q_INVOKABLE void invokeThemeUpdate();
    Q_INVOKABLE void invokeChangePage(int ipage);
    Q_INVOKABLE void invokeScan();
    Q_INVOKABLE void invokeConnectDevice(QString address);
    Q_INVOKABLE void invokeDisconnectDevice(QString address);

    Q_INVOKABLE void invokeCancel();
    Q_INVOKABLE void invokeExit();

    Q_INVOKABLE void invokeSaveCurrentPage(QString page);
    Q_INVOKABLE QString invokeRetreiveLastPage();

    Q_PROPERTY (bool IsDarkTheme READ getIsDarkTheme WRITE setIsDarkTheme NOTIFY IsDarkThemeChanged)
    bool getIsDarkTheme();
    void setIsDarkTheme(bool isdarktheme);

    Q_PROPERTY (QString CurrentDeviceAddress READ getCurrentDeviceAddress WRITE setCurrentDeviceAddress NOTIFY CurrentDeviceAddressChanged)
    void setCurrentDeviceAddress(QString dev_addr);
    QString getCurrentDeviceAddress();

    Q_PROPERTY (QList<Device> DeviceList READ getDeviceList WRITE setDeviceList NOTIFY DeviceListChanged)
    void setDeviceList(QList<Device> devlist);
    QList<Device> getDeviceList();

    Q_PROPERTY (bool ShowIndicator READ getShowIndicator NOTIFY ShowIndicatorChanged)
    bool getShowIndicator();

    Q_PROPERTY (ApplicationTheme Theme READ getTheme NOTIFY ThemeChanged)
    ApplicationTheme getTheme();

    Q_PROPERTY (QList<ApplicationMenu> Menu READ getMenu NOTIFY MenuChanged)
    QList<ApplicationMenu> getMenu();

    Q_PROPERTY (QString TraceString READ getTraceString NOTIFY TraceStringChanged)
    QString getTraceString();

    Q_PROPERTY (QString ScanLog READ getScanLog NOTIFY ScanLogChanged)
    QString getScanLog();

    void Initialize();
    void Trace(QString str);
    void ClearTrace();
    void ClearScanLog();
    void TraceScanResult(QString str);

signals:
    void ThemeChanged();
    void MenuChanged();
    void ShowIndicatorChanged();
    void IsDarkThemeChanged();
    void IsTraceEnabledChanged();
    void TraceStringChanged();

    void CurrentDeviceAddressChanged();
    void DeviceListChanged();

    //UI events and operations states
    void deviceAction();
    void deviceMessage(bool fl, QString str);
    void pageAction(int ipage);

    //Specifc errors

    //Trace/progress
    void initializationComplete();

    //UI Indicators
    void progressIndicatorsOff();
    void progressIndicatorsOn();
    void networkIndicatorsOff();
    void networkIndicatorsOn();

    //Scanning
    void scanFinished();
    void ScanLogChanged();

private slots:

private:
    QGuiApplication* app;

    //Object lists
    QList<Device> deviceList_;
    QList<ApplicationMenu> menuItemList_;
    QMap<QString, Device> deviceMap_;

    //Globals / Miscellanous
    QString lastPage_;

    bool isDarkTheme_;
    ApplicationTheme theme_;
    QString traceString_;
    QString scanLog_;

    QString currentDeviceAddress_;
};

extern Controller* controllerInstance;

#endif
