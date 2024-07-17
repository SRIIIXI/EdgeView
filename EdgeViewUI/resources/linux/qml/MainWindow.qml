import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

ApplicationWindow
{
    Material.theme: Material.Dark
    Material.accent: "#1e90ff"

    id: appWindow
    width: 1024
    height: 768
    visible: true
    title: qsTr("Edge View")

    minimumWidth: 1024
    minimumHeight: 768

    property bool is_dark_theme: false
    property int menu_width: 250

    Rectangle
    {
        id: header
        width: appWindow.width - menu_width
        height: 50
        anchors.left: sideMenuRect.right

        ToolButton
        {
            id: userIcon
            height: 40
            width: 40
            icon.source: "../images/Profile.png"
            icon.color: "transparent"
            anchors.right: header.right
            anchors.rightMargin: 20
            anchors.leftMargin: 20
            anchors.verticalCenter: header.verticalCenter
        }

        Text
        {
            id: userName
            width: 200
            text: "Subrato Roy"
            font.bold: false
            anchors.leftMargin: 20
            anchors.right: userIcon.left
            anchors.verticalCenter: header.verticalCenter
            horizontalAlignment: Text.AlignRight
        }

        Switch
        {
            id: themeSelector
            height: 20
            Material.theme: Material.Light
            Material.accent: "#1e90ff"
            anchors.leftMargin: 20
            anchors.right: userName.left
            anchors.verticalCenter: header.verticalCenter
        }

        Text
        {
            id: appTitle
            text: "Edge View"
            font.bold: true
            anchors.leftMargin: 20
            anchors.left: header.left
            anchors.verticalCenter: header.verticalCenter
        }
    }

    Rectangle
    {
        id: headerline
        width: appWindow.width - menu_width
        height: 1
        border.width: 1
        border.color: "lightgrey"
        anchors.top: header.bottom
        anchors.left: sideMenuRect.right
    }

    Rectangle
    {
        id: sideMenuRect
        width: menu_width
        height: appWindow.height
        anchors.top: appWindow.top
        color: "transparent"

        Drawer
        {
            id: sideMenu
            height: sideMenuRect.height
            width: sideMenuRect.width
            modal: false
            interactive: false
            position: 52
            visible: true

            Column
            {
                anchors.fill: parent

                ItemDelegate
                {
                    icon
                    {
                       source: "../images/EdgeView.png"
                       height: 50
                    }
                    anchors.horizontalCenter: parent.horizontalCenter
                    enabled: false
                }

                ItemDelegate
                {
                    text: qsTr("Dashboard")
                    width: parent.width

                    onClicked:
                    {
                        stackView.pop()
                        stackView.push("Dashboard.qml")
                    }

                    icon
                    {
                       source: "../images/Home.png"
                       width: 35
                       height: 35
                    }

                    enabled:
                    {
                        //if(applicationData.CurrentMeterSerialNo === "")
                        //{
                        //    return false
                        //}

                        return true
                    }
                }

                ItemDelegate
                {
                    text: qsTr("Devices")
                    width: parent.width

                    onClicked:
                    {
                        //drawer.close()
                        //applicationData.invokeSaveCurrentPage("Dashboard.qml")
                        //stackView.pop()
                        //stackView.push("Dashboard.qml")
                    }

                    icon
                    {
                       source: "../images/Device.png"
                       width: 35
                       height: 35
                    }

                    enabled:
                    {
                        //if(applicationData.CurrentMeterSerialNo === "")
                        //{
                        //    return false
                        //}

                        return true
                    }
                }

                ItemDelegate
                {
                    text: qsTr("Tenants")
                    width: parent.width

                    onClicked:
                    {
                        //drawer.close()
                        //applicationData.invokeSaveCurrentPage("Dashboard.qml")
                        //stackView.pop()
                        //stackView.push("Dashboard.qml")
                    }

                    icon
                    {
                       source: "../images/Tenant.png"
                       width: 35
                       height: 35
                    }

                    enabled:
                    {
                        //if(applicationData.CurrentMeterSerialNo === "")
                        //{
                        //    return false
                        //}

                        return true
                    }
                }

                ItemDelegate
                {
                    text: qsTr("Sites")
                    width: parent.width

                    onClicked:
                    {
                        //drawer.close()
                        //applicationData.invokeSaveCurrentPage("Dashboard.qml")
                        //stackView.pop()
                        //stackView.push("Dashboard.qml")
                    }

                    icon
                    {
                       source: "../images/Site.png"
                       width: 35
                       height: 35
                    }

                    enabled:
                    {
                        //if(applicationData.CurrentMeterSerialNo === "")
                        //{
                        //    return false
                        //}

                        return true
                    }
                }

                ItemDelegate
                {
                    text: qsTr("Users")
                    width: parent.width

                    onClicked:
                    {
                        //drawer.close()
                        //applicationData.invokeSaveCurrentPage("Dashboard.qml")
                        //stackView.pop()
                        //stackView.push("Dashboard.qml")
                    }

                    icon
                    {
                       source: "../images/User.png"
                       width: 35
                       height: 35
                    }

                    enabled:
                    {
                        //if(applicationData.CurrentMeterSerialNo === "")
                        //{
                        //    return false
                        //}

                        return true
                    }
                }

                ItemDelegate
                {
                    text: qsTr("Asset Management")
                    width: parent.width

                    onClicked:
                    {
                        //drawer.close()
                        //applicationData.invokeSaveCurrentPage("Dashboard.qml")
                        //stackView.pop()
                        //stackView.push("Dashboard.qml")
                    }

                    icon
                    {
                       source: "../images/Asset.png"
                       width: 35
                       height: 35
                    }

                    enabled:
                    {
                        //if(applicationData.CurrentMeterSerialNo === "")
                        //{
                        //    return false
                        //}

                        return true
                    }
                }

                ItemDelegate
                {
                    text: qsTr("Environmental Monitoring")
                    width: parent.width

                    onClicked:
                    {
                        //drawer.close()
                        //applicationData.invokeSaveCurrentPage("Dashboard.qml")
                        //stackView.pop()
                        //stackView.push("Dashboard.qml")
                    }

                    icon
                    {
                       source: "../images/Environment.png"
                       width: 35
                       height: 35
                    }

                    enabled:
                    {
                        //if(applicationData.CurrentMeterSerialNo === "")
                        //{
                        //    return false
                        //}

                        return true
                    }
                }

                ItemDelegate
                {
                    text: qsTr("Meter Data Management")
                    width: parent.width

                    onClicked:
                    {
                        //drawer.close()
                        //applicationData.invokeSaveCurrentPage("Dashboard.qml")
                        //stackView.pop()
                        //stackView.push("Dashboard.qml")
                    }

                    icon
                    {
                       source: "../images/Meter.png"
                       width: 35
                       height: 35
                    }

                    enabled:
                    {
                        //if(applicationData.CurrentMeterSerialNo === "")
                        //{
                        //    return false
                        //}

                        return true
                    }
                }
            }
        }
    }

    Rectangle
    {
        id: verticalBorder
        width: 1
        height: appWindow.height
        border.width: 1
        border.color: "lightgrey"
        anchors.top: appWindow.top
        anchors.left: sideMenuRect.right
    }

    ScrollView
    {
        height: appWindow.height - header.height - headerline.height
        width: appWindow.width - sideMenuRect.width
        anchors.top: headerline.bottom
        anchors.left: verticalBorder.right

        StackView
        {
            id: stackView
            anchors.fill: parent
        }
    }
}
