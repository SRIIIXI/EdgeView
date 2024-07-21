import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
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
    }

    Rectangle
    {
        id: brandingArea
        height: applicationData.Theme.BarHeight * 2
        width: 220
        color: applicationData.Theme.BackgroundColor
        anchors.top: parent.top
        anchors.left: parent.left

        Image
        {
            id: appLogo
            source: "../images/EdgeView.png"
            height: parent.height * 0.9
            width: parent.height * 0.9
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Header
    {
        id: headerPanel
        height: applicationData.Theme.BarHeight * 2
        width: parent.width -  brandingArea.width
        anchors.top: parent.top
        anchors.right: parent.right
        headerTitle: "Edge Manager"
    }

    Rectangle
    {
        id: menuArea
        height: parent.height - applicationData.Theme.BarHeight * 2
        width: 220
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: applicationData.Theme.BackgroundColor

        ListView
        {
            id: menuListView
            height: parent.height*0.95 - applicationData.Theme.BarHeight
            width: parent.width*0.96
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            visible: true
            spacing: 5
            clip: true
            model: menuModel
            delegate: menuDelegate

            onCurrentIndexChanged:
            {
                applicationData.invokeChangePage(currentIndex);
            }
        }

        Component
        {
            id: menuDelegate

            Rectangle
            {
                id: menuItem
                width: menuListView.width
                height: applicationData.Theme.BarHeight*0.9
                radius: 5
                color: applicationData.Theme.ControlColor
                border.color: applicationData.Theme.ControlLowColor

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        menuListView.currentIndex = index
                    }
                }

                Image
                {
                    id: menuImg
                    source: menuModel[index].ItemIcon
                    width: menuItem.height*0.65
                    height: menuItem.height*0.65
                    anchors.verticalCenter: parent.verticalCenter
                    anchors
                    {
                        left: parent.left
                        leftMargin:  10
                    }
                }

                Label
                {
                    id:menuNamelbl
                    font.pointSize: headerPanel.fontSizeSmall
                    color: applicationData.Theme.FontColor
                    elide: Label.ElideRight
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors
                    {
                        left: menuImg.right
                        leftMargin: 30
                    }

                    text: menuModel[index].ItemName

                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            menuListView.currentIndex = index
                        }
                    }
                }
            }
        }

        RoundButton
        {
            id: exitButton
            height: applicationData.Theme.BarHeight
            width: applicationData.Theme.BarHeight
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            Image
            {
                id: exitButtonImg
                source:
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

                width: exitButton.height*0.5
                height: exitButton.height*0.5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
            onClicked:
            {
                applicationData.invokeExit();
            }
        }
    }

    StackView
    {
        id: stackView
        height: parent.height - applicationData.Theme.BarHeight * 2 - 2
        width: parent.width -  menuArea.width - 2
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }

    Rectangle
    {
        id: horizontalBorder
        height: 1
        width: mainView.width
        anchors.top: brandingArea.bottom
        anchors.left: mainView.left
        radius: 0
        color: applicationData.Theme.ControlLowColor
    }

    Rectangle
    {
        id: verticalBorder
        height: mainView.height
        width: 1
        anchors.top: mainView.top
        anchors.left: brandingArea.right
        radius: 0
        color: applicationData.Theme.ControlLowColor
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
