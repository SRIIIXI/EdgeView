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

    Component.onCompleted:
    {
        updateMenu("home")
        homePage.visible = true
        //stackView.push("Home.qml")
    }

    Label
    {
        id: dummy
    }

    Rectangle
    {
        id: userArea
        height: applicationData.Theme.BarHeight*2
        width:  200
        color: applicationData.Theme.BackgroundColor
        anchors.top: parent.top
        anchors.left: parent.left

        Rectangle
        {
            id: userImageRect
            width: parent.height*0.5
            height: parent.height*0.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            radius: height*0.5
            border.width: 1
            border.color: "black"
            // Image
            // {
            //     id: name
            //     source: "../images/SampleUser.png"
            //     anchors.fill: parent
            // }
        }

        Label
        {
            text: "Logged User"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.bottom
            color: applicationData.Theme.FontColor
        }
    }

    Rectangle
    {
        id: menuArea
        width: 200
        height: parent.height - userArea.height
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
        anchors.top: userArea.bottom

        CustomMenuItem
        {
            id: menuHome
            menuWidth: 200
            menuHeight: applicationData.Theme.BarHeight
            anchors.top: parent.top
            anchors.left: parent.left
            text: "Home"
            isActive: false
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
                //stackView.pop()
                //stackView.push("Home.qml")
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
                //stackView.pop()
                //stackView.push("Enterprises.qml")
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
                //stackView.pop()
                //stackView.push("Sites.qml")
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
                //stackView.pop()
                //stackView.push("Areas.qml")
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
                //stackView.pop()
                //stackView.push("Devices.qml")
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
                //stackView.pop()
                //stackView.push("Assets.qml")
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
                //stackView.pop()
                //stackView.push("Rules.qml")
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
                //stackView.pop()
                //stackView.push("Roles.qml")
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
                //stackView.pop()
                //stackView.push("Users.qml")
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
                //stackView.pop()
                //stackView.push("Telemetry.qml")
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
                //stackView.pop()
                //stackView.push("Alarms.qml")
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

    //StackView
    //{
    //    id: stackView
    //    height: parent.height - applicationData.Theme.BarHeight
    //    width: parent.width -  menuArea.width
    //    anchors.bottom: parent.bottom
    //    anchors.right: parent.right
    //}

    Rectangle
    {
        id: clientArea
        height: parent.height - applicationData.Theme.BarHeight
        width: parent.width -  menuArea.width
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        Home
        {
            id: homePage
            anchors.fill: parent
            visible: false
        }

        Enterprises
        {
            id: enterprisesPage
            anchors.fill: parent
            visible: false
        }

        Sites
        {
            id: sitesPage
            anchors.fill: parent
            visible: false
        }

        Areas
        {
            id: areasPage
            anchors.fill: parent
            visible: false
        }

        Devices
        {
            id: devicesPage
            anchors.fill: parent
            visible: false
        }

        Assets
        {
            id: assetsPage
            anchors.fill: parent
            visible: false
        }

        Rules
        {
            id: rulesPage
            anchors.fill: parent
            visible: false
        }

        Roles
        {
            id: rolesPage
            anchors.fill: parent
            visible: false
        }

        Users
        {
            id: usersPage
            anchors.fill: parent
            visible: false
        }

        Telemetry
        {
            id: telemetryPage
            anchors.fill: parent
            visible: false
        }

        Alarms
        {
            id: alarmsPage
            anchors.fill: parent
            visible: false
        }
    }

    Rectangle
    {
        id: horizontalBorder
        height: 1
        width: mainView.width - userArea.width
        anchors.top: headerPanel.bottom
        anchors.left: userArea.right
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

        homePage.visible = false;
        enterprisesPage.visible = false;
        sitesPage.visible = false;
        areasPage.visible = false;
        devicesPage.visible = false;
        assetsPage.visible = false;
        rulesPage.visible = false;
        rolesPage.visible = false;
        usersPage.visible = false;
        telemetryPage.visible = false;
        alarmsPage.visible = false;

        switch(menuname)
        {
        case "home":
        {
            menuHome.isActive = true;
            homePage.visible = true;
            break;
        }
        case "enterprises":
        {
            menuEnterprises.isActive = true;
            enterprisesPage.visible = true;
            break;
        }
        case "sites":
        {
            menuSites.isActive = true;
            sitesPage.visible = true;
            break;
        }
        case "areas":
        {
            menuAreas.isActive = true;
            areasPage.visible = true;
            break;
        }
        case "devices":
        {
            menuDevices.isActive = true;
            devicesPage.visible = true;
            break;
        }
        case "assets":
        {
            menuAssets.isActive = true;
            assetsPage.visible = true;
            break;
        }
        case "rules":
        {
            menuRules.isActive = true;
            rulesPage.visible = true;
            break;
        }
        case "roles":
        {
            menuRoles.isActive = true;
            rolesPage.visible = true;
            break;
        }
        case "users":
        {
            menuUsers.isActive = true;
            usersPage.visible = true;
            break;
        }
        case "telemetry":
        {
            menuTelemetry.isActive = true;
            telemetryPage.visible = true;
            break;
        }
        case "alarms":
        {
            menuAlarms.isActive = true;
            alarmsPage.visible = true;
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
                //stackView.pop();
                applicationData.invokeSaveCurrentPage("Home.qml")
                //stackView.push("Home.qml");
            }

            if(pg === 1)
            {
                //stackView.pop();
                applicationData.invokeSaveCurrentPage("Enterprises.qml")
                //stackView.push("Enterprises.qml");
            }

            if(pg === 2)
            {
                //stackView.pop();
                applicationData.invokeSaveCurrentPage("Sites.qml")
                //stackView.push("Sites.qml");
            }

            if(pg === 3)
            {
                //stackView.pop();
                applicationData.invokeSaveCurrentPage("Areas.qml")
                //stackView.push("Areas.qml");
            }

            if(pg === 4)
            {
                //stackView.pop();
                applicationData.invokeSaveCurrentPage("Devices.qml")
                //stackView.push("Devices.qml");
            }

            if(pg === 5)
            {
                //stackView.pop();
                applicationData.invokeSaveCurrentPage("Assets.qml")
                //stackView.push("Assets.qml");
            }

            if(pg === 6)
            {
                //stackView.pop();
                applicationData.invokeSaveCurrentPage("Rules.qml")
                //stackView.push("Rules.qml");
            }

            if(pg === 7)
            {
                //stackView.pop();
                applicationData.invokeSaveCurrentPage("Roles.qml")
                //stackView.push("Roles.qml");
            }

            if(pg === 8)
            {
                //stackView.pop();
                applicationData.invokeSaveCurrentPage("Users.qml")
                //stackView.push("Users.qml");
            }

            if(pg === 9)
            {
                //stackView.pop();
                applicationData.invokeSaveCurrentPage("Telemetry.qml")
                //stackView.push("Telemetry.qml");
            }

            if(pg === 10)
            {
                //stackView.pop();
                applicationData.invokeSaveCurrentPage("Alarms.qml")
                //stackView.push("Alarms.qml");
            }
        }
    }
}
