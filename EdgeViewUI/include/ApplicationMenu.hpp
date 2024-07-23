#ifndef APPLICATION_MENU
#define APPLICATION_MENU

#include <QObject>

class ApplicationMenu
{
public:
    Q_GADGET

public:
    bool IsAdmin_;
public:
    QString ItemName_;
public:
    QString ItemTarget_;
public:
    QString ItemIcon_;
public:
    bool IsSelected_;
public:
    Q_PROPERTY(bool IsAdmin MEMBER IsAdmin_)
    Q_PROPERTY(QString ItemName MEMBER ItemName_)
    Q_PROPERTY(QString ItemTarget MEMBER ItemTarget_)
    Q_PROPERTY(QString ItemIcon MEMBER ItemIcon_)
    Q_PROPERTY(bool IsSelected MEMBER IsSelected_)

public:
    ~ApplicationMenu()
    {

    }

    ApplicationMenu()
    {

    }

    ApplicationMenu(bool iIsAdmin,
                     QString iItemName,
                     QString iItemTarget,
                     QString iItemIcon,
                    bool iIsSelected = false)
    {
        IsAdmin_ = iIsAdmin;
        ItemName_ = iItemName;
        ItemTarget_ = iItemTarget;
        ItemIcon_ = iItemIcon;
        IsSelected_= iIsSelected;
    }

    ApplicationMenu(const ApplicationMenu& other)
    {
        IsAdmin_ = other.IsAdmin_;
        ItemName_ = other.ItemName_;
        ItemTarget_ = other.ItemTarget_;
        ItemIcon_ = other.ItemIcon_;
        IsSelected_ = other.IsSelected_;
    }

    ApplicationMenu& operator = (const ApplicationMenu& other)
    {
        IsAdmin_ = other.IsAdmin_;
        ItemName_ = other.ItemName_;
        ItemTarget_ = other.ItemTarget_;
        ItemIcon_ = other.ItemIcon_;
        IsSelected_ = other.IsSelected_;
        return *this;
    }
};

#endif
