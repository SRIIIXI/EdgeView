#ifndef APPLICATION_THEME
#define APPLICATION_THEME

#include <QObject>

class ApplicationTheme
{
public:
    Q_GADGET

public:
    bool IsDarkMode_;
public:
    QString FontColor_;
public:
    QString AccentColor_;
public:
    QString AccentLowColor_;
public:
    QString BackgroundColor_;
public:
    QString ControlColor_;
public:
    QString ControlLowColor_;
public:
    uint32_t BarHeight_;
public:
    Q_PROPERTY(bool IsDarkMode MEMBER IsDarkMode_)
    Q_PROPERTY(QString FontColor MEMBER FontColor_)
    Q_PROPERTY(QString AccentColor MEMBER AccentColor_)
    Q_PROPERTY(QString AccentLowColor MEMBER AccentLowColor_)
    Q_PROPERTY(QString BackgroundColor MEMBER BackgroundColor_)
    Q_PROPERTY(QString ControlColor MEMBER ControlColor_)
    Q_PROPERTY(QString ControlLowColor MEMBER ControlLowColor_)
    Q_PROPERTY(uint32_t BarHeight MEMBER BarHeight_)

public:
    ~ApplicationTheme()
    {

    }

    ApplicationTheme()
    {

    }

    ApplicationTheme(bool iIsDarkMode,
                     QString iFontColor,
                     QString iAccentColor,
                     QString iAccentLowColor,
                     QString iBackgroundColor,
                     QString iControlColor,
                     QString iControlLowColor,
                     uint32_t iBarHeight)
    {
        IsDarkMode_ = iIsDarkMode;
        FontColor_ = iFontColor;
        AccentColor_ = iAccentColor;
        AccentLowColor_ = iAccentLowColor;
        BackgroundColor_ = iBackgroundColor;
        ControlColor_ = iControlColor;
        ControlLowColor_ = iControlLowColor;
        BarHeight_ = iBarHeight;
    }

    ApplicationTheme(const ApplicationTheme& other)
    {
        IsDarkMode_ = other.IsDarkMode_;
        FontColor_ = other.FontColor_;
        AccentColor_ = other.AccentColor_;
        AccentLowColor_ = other.AccentLowColor_;
        BackgroundColor_ = other.BackgroundColor_;
        ControlColor_ = other.ControlColor_;
        ControlLowColor_ = other.ControlLowColor_;
        BarHeight_ = other.BarHeight_;
    }

    ApplicationTheme& operator = (const ApplicationTheme& other)
    {
        IsDarkMode_ = other.IsDarkMode_;
        FontColor_ = other.FontColor_;
        AccentColor_ = other.AccentColor_;
        AccentLowColor_ = other.AccentLowColor_;
        BackgroundColor_ = other.BackgroundColor_;
        ControlColor_ = other.ControlColor_;
        ControlLowColor_ = other.ControlLowColor_;
        BarHeight_ = other.BarHeight_;
        return *this;
    }

    void EnableDarkMode()
    {
        IsDarkMode_ = true;
        FontColor_ = "#ffffff";
        AccentColor_ = "#1e90ff";
        AccentLowColor_ = "#00bfff";
        BackgroundColor_ = "#000000";
        ControlColor_ = "#1C2833";
        ControlLowColor_ = "#304256";
        BarHeight_ = 45;
    }

    void EnableLightMode()
    {
        IsDarkMode_ = false;
        FontColor_ = "#000000";
        AccentColor_ = "#1e90ff";
        AccentLowColor_ = "#00bfff";
        BackgroundColor_ = "#ffffff";
        ControlColor_ = "#f5f5f5";
        ControlLowColor_ = "#989ea8";
        BarHeight_ = 45;
    }
};

#endif
