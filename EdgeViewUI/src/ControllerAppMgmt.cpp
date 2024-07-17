#include "Controller.hpp"

void Controller::invokeChangePage(int ipage)
{
    emit pageAction(ipage);
}

void Controller::invokeThemeUpdate()
{
    if(app->palette().window().color().value() > app->palette().windowText().color().value())
    {
        isDarkTheme_ = false;
    }
    else
    {
        isDarkTheme_ = true;
    }

    emit IsDarkThemeChanged();
}

void Controller::invokeSaveCurrentPage(QString page)
{
    lastPage_ = page;
}

QString Controller::invokeRetreiveLastPage()
{
    return lastPage_;
}

bool Controller::getShowIndicator()
{
    if(lastPage_ == "AddToken.qml"
        || lastPage_ == "AddMeter.qml"
        || lastPage_ == "AddTariff.qml"
        || lastPage_ == "AvailableTokens.qml"
        || lastPage_ == "AvailableMeters.qml"
        || lastPage_ == "AvailableTariff.qml"
        || lastPage_ == "Dashboard.qml"
        || lastPage_ == "Energy.qml"
        || lastPage_ == "PowerQuality.qml"
        || lastPage_ == "Alarms.qml"
        || lastPage_ == "Trace.qml")
    {
        return true;
    }

    return false;
}

bool Controller::getIsDarkTheme()
{
    return isDarkTheme_;
}

void Controller::setIsDarkTheme(bool isdarktheme)
{
    isDarkTheme_ = isdarktheme;

    if(isDarkTheme_)
    {
        theme_.EnableDarkMode();
    }
    else
    {
        theme_.EnableLightMode();
    }

    emit IsDarkThemeChanged();
    emit ThemeChanged();
}

ApplicationTheme Controller::getTheme()
{
    return theme_;
}

void Controller::Trace(QString str)
{
    str = QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss ") + str + "\n";
    qDebug() << str;

    if(traceString_.length() > 1024*1024)
    {
        traceString_.clear();
    }

    traceString_ = str + traceString_;
    emit TraceStringChanged();
}

void Controller::ClearTrace()
{
    traceString_.clear();
    emit TraceStringChanged();
}

QString Controller::getTraceString()
{
    return traceString_;
}

void Controller::TraceScanResult(QString str)
{
    str = str + "\n";

    if(scanLog_.length() > 1024*1024)
    {
        scanLog_.clear();
    }

    scanLog_ = str + scanLog_;
    emit ScanLogChanged();
}

void Controller::ClearScanLog()
{
    scanLog_.clear();
    emit ScanLogChanged();
}

QString Controller::getScanLog()
{
    return scanLog_;
}
