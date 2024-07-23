#include "Controller.hpp"

void Controller::invokeChangePage(int ipage)
{
    for(int x = 0; x < menuItemList_.count(); x++)
    {
        menuItemList_[ipage].IsSelected_ = false;

    }

    menuItemList_[ipage].IsSelected_ = true;

    //emit MenuChanged();
    emit menuAction();
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

QList<ApplicationMenu> Controller::getMenu()
{
    return menuItemList_;
}
