import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.3
import QtQuick.Layouts 1.3

ApplicationWindow
{
    id: mainView

    objectName: "mainViewID"
    visible: true

    minimumHeight: 768
    minimumWidth: 1024

    property int iconHeight : width*0.075
    property int iconWidth : width*0.075
    property string oldPage: ""
    property bool isClosing: false

    property variant menuModel :  []

    Component.onCompleted:
    {
        stackView.push("Home.qml")
        menuModel = applicationData.Menu
        //menuArea.open()
    }

    Rectangle
    {
        id: logoArea
        height: applicationData.Theme.BarHeight
        width:  200
        color: applicationData.Theme.BackgroundColor
        anchors.top: parent.top
        anchors.left: parent.left
        Image
        {
            id: name
            source: "../images/EdgeView.png"
            width: parent.height*0.75
            height: parent.height*0.75
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Rectangle
    {
        id: menuArea
        width: 200
        height: parent.height - logoArea.height
        color:
        if(applicationData.IsDarkTheme === true)
        {
            return "darkgrey";
        }
        else
        {
            return "lightgrey";
        }
        anchors.left: parent.left
        anchors.top: logoArea.bottom

        CustomMenuItem
        {
            id: menuHome
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: parent.top
            anchors.left: parent.left
            text: "Home"
            isActive: true
            menuIconSource:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return "../images/HomeWhite.png";
                }
                else
                {
                    return "../images/HomeBlack.png";
                }
            }
            textColor: applicationData.Theme.FontColor
            onClicked:
            {
                updateMenu("home")
                applicationData.invokeSaveCurrentPage("Home.qml")
                stackView.pop()
                stackView.push("Home.qml")
            }
        }

        CustomMenuItem
        {
            id: menuEnterprises
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: menuHome.bottom
            anchors.left: parent.left
            text: "Enterprises"
            isActive: false
            menuIconSource:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return "../images/EnterprisesWhite.png";
                }
                else
                {
                    return "../images/EnterprisesBlack.png";
                }
            }
            textColor: applicationData.Theme.FontColor
            onClicked:
            {
                updateMenu("enterprises")
                applicationData.invokeSaveCurrentPage("Enterprises.qml")
                stackView.pop()
                stackView.push("Enterprises.qml")
            }
        }

        CustomMenuItem
        {
            id: menuSites
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: menuEnterprises.bottom
            anchors.left: parent.left
            text: "Sites"
            isActive: false
            menuIconSource:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return "../images/SitesWhite.png";
                }
                else
                {
                    return "../images/SitesBlack.png";
                }
            }
            textColor: applicationData.Theme.FontColor
            onClicked:
            {
                updateMenu("sites")
                applicationData.invokeSaveCurrentPage("Sites.qml")
                stackView.pop()
                stackView.push("Sites.qml")
            }
        }

        CustomMenuItem
        {
            id: menuAreas
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: menuSites.bottom
            anchors.left: parent.left
            text: "Areas"
            isActive: false
            menuIconSource:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return "../images/AreasWhite.png";
                }
                else
                {
                    return "../images/AreasBlack.png";
                }
            }
            textColor: applicationData.Theme.FontColor
            onClicked:
            {
                updateMenu("areas")
                applicationData.invokeSaveCurrentPage("Areas.qml")
                stackView.pop()
                stackView.push("Areas.qml")
            }
        }

        CustomMenuItem
        {
            id: menuDevices
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: menuAreas.bottom
            anchors.left: parent.left
            text: "Devices"
            isActive: false
            menuIconSource:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return "../images/DevicesWhite.png";
                }
                else
                {
                    return "../images/DevicesBlack.png";
                }
            }
            textColor: applicationData.Theme.FontColor
            onClicked:
            {
                updateMenu("devices")
                applicationData.invokeSaveCurrentPage("Devices.qml")
                stackView.pop()
                stackView.push("Devices.qml")
            }
        }

        CustomMenuItem
        {
            id: menuAssets
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: menuDevices.bottom
            anchors.left: parent.left
            text: "Assets"
            isActive: false
            menuIconSource:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return "../images/AssetsWhite.png";
                }
                else
                {
                    return "../images/AssetsBlack.png";
                }
            }
            textColor: applicationData.Theme.FontColor
            onClicked:
            {
                updateMenu("assets")
                applicationData.invokeSaveCurrentPage("Assets.qml")
                stackView.pop()
                stackView.push("Assets.qml")
            }
        }

        CustomMenuItem
        {
            id: menuRules
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: menuAssets.bottom
            anchors.left: parent.left
            text: "Rules"
            isActive: false
            menuIconSource:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return "../images/RulesWhite.png";
                }
                else
                {
                    return "../images/RulesBlack.png";
                }
            }
            textColor: applicationData.Theme.FontColor
            onClicked:
            {
                updateMenu("rules")
                applicationData.invokeSaveCurrentPage("Rules.qml")
                stackView.pop()
                stackView.push("Rules.qml")
            }
        }

        CustomMenuItem
        {
            id: menuRoles
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: menuRules.bottom
            anchors.left: parent.left
            text: "Roles"
            isActive: false
            menuIconSource:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return "../images/RolesWhite.png";
                }
                else
                {
                    return "../images/RolesBlack.png";
                }
            }
            textColor: applicationData.Theme.FontColor
            onClicked:
            {
                updateMenu("roles")
                applicationData.invokeSaveCurrentPage("Roles.qml")
                stackView.pop()
                stackView.push("Roles.qml")
            }
        }

        CustomMenuItem
        {
            id: menuUsers
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: menuRoles.bottom
            anchors.left: parent.left
            text: "Users"
            isActive: false
            menuIconSource:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return "../images/UsersWhite.png";
                }
                else
                {
                    return "../images/UsersBlack.png";
                }
            }
            textColor: applicationData.Theme.FontColor
            onClicked:
            {
                updateMenu("users");
                applicationData.invokeSaveCurrentPage("Users.qml")
                stackView.pop()
                stackView.push("Users.qml")
            }
        }

        CustomMenuItem
        {
            id: menuTelemetry
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: menuUsers.bottom
            anchors.left: parent.left
            text: "Telemetry"
            isActive: false
            menuIconSource:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return "../images/TelemetryWhite.png";
                }
                else
                {
                    return "../images/TelemetryBlack.png";
                }
            }
            textColor: applicationData.Theme.FontColor
            onClicked:
            {
                updateMenu("telemetry")
                applicationData.invokeSaveCurrentPage("Telemetry.qml")
                stackView.pop()
                stackView.push("Telemetry.qml")
            }
        }

        CustomMenuItem
        {
            id: menuAlarms
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: menuTelemetry.bottom
            anchors.left: parent.left
            text: "Alarms"
            isActive: false
            menuIconSource:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return "../images/AlarmsWhite.png";
                }
                else
                {
                    return "../images/AlarmsBlack.png";
                }
            }
            textColor: applicationData.Theme.FontColor
            onClicked:
            {
                updateMenu("alarms")
                applicationData.invokeSaveCurrentPage("Alarms.qml")
                stackView.pop()
                stackView.push("Alarms.qml")
            }
        }

        CustomMenuItem
        {
            id: menuExit
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: menuAlarms.bottom
            anchors.left: parent.left
            text: "Exit"
            isActive: false
            menuIconSource:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return "../images/ExitWhite.png";
                }
                else
                {
                    return "../images/ExitBlack.png";
                }
            }
            textColor: applicationData.Theme.FontColor
            onClicked:
            {
                applicationData.invokeExit();
            }
        }
    }

    Header
    {
        id: headerPanel
        height: applicationData.Theme.BarHeight
        width: parent.width -  menuArea.width
        anchors.top: parent.top
        anchors.right: parent.right
        headerTitle: "Edge Manager"
    }

    StackView
    {
        id: stackView
        height: parent.height - applicationData.Theme.BarHeight
        width: parent.width -  menuArea.width
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }

    Rectangle
    {
        id: horizontalBorder
        height: 1
        width: mainView.width
        anchors.top: headerPanel.bottom
        anchors.left: mainView.left
        radius: 0
        color: applicationData.Theme.ControlLowColor
    }

    function updateMenu(menuname)
    {
        menuAlarms.isActive = false;
        menuAreas.isActive = false;
        menuAssets.isActive = false;
        menuDevices.isActive = false;
        menuEnterprises.isActive = false;
        menuHome.isActive = false;
        menuRoles.isActive = false;
        menuRules.isActive = false;
        menuSites.isActive = false;
        menuTelemetry.isActive = false;
        menuUsers.isActive = false;

        switch(menuname)
        {
        case "home":
        {
            menuHome.isActive = true;
            break;
        }
        case "enterprises":
        {
            menuEnterprises.isActive = true;
            break;
        }
        case "sites":
        {
            menuSites.isActive = true;
            break;
        }
        case "areas":
        {
            menuAreas.isActive = true;
            break;
        }
        case "devices":
        {
            menuDevices.isActive = true;
            break;
        }
        case "assets":
        {
            menuAssets.isActive = true;
            break;
        }
        case "rules":
        {
            menuRules.isActive = true;
            break;
        }
        case "roles":
        {
            menuRoles.isActive = true;
            break;
        }
        case "users":
        {
            menuUsers.isActive = true;
            break;
        }
        case "telemetry":
        {
            menuTelemetry.isActive = true;
            break;
        }
        case "alarms":
        {
            menuAlarms.isActive = true;
            break;
        }
        }
    }

    Connections
    {
        target: applicationData

        function onMenuAction()
        {
            menuModel = applicationData.Menu
        }

        function onPageAction(pg)
        {
            if(pg === 0)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("Home.qml")
                stackView.push("Home.qml");
            }

            if(pg === 1)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("Enterprises.qml")
                stackView.push("Enterprises.qml");
            }

            if(pg === 2)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("Sites.qml")
                stackView.push("Sites.qml");
            }

            if(pg === 3)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("Areas.qml")
                stackView.push("Areas.qml");
            }

            if(pg === 4)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("Devices.qml")
                stackView.push("Devices.qml");
            }

            if(pg === 5)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("Assets.qml")
                stackView.push("Assets.qml");
            }

            if(pg === 6)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("Rules.qml")
                stackView.push("Rules.qml");
            }

            if(pg === 7)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("Roles.qml")
                stackView.push("Roles.qml");
            }

            if(pg === 8)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("Users.qml")
                stackView.push("Users.qml");
            }

            if(pg === 9)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("Telemetry.qml")
                stackView.push("Telemetry.qml");
            }

            if(pg === 10)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("Alarms.qml")
                stackView.push("Alarms.qml");
            }
        }
    }
}
