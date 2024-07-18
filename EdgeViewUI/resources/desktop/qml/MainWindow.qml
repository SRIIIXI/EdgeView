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

    onClosing:
    {
        close.accepted = isClosing;
    }

    Component.onCompleted:
    {
        stackView.push("Home.qml")
    }

    Rectangle
    {
        id: brandingArea
        height: applicationData.Theme.BarHeight * 2
        width: 220
        color: "green"
        anchors.top: parent.top
        anchors.left: parent.left
    }

    Header
    {
        id: headerPanel
        height: applicationData.Theme.BarHeight * 2
        width: parent.width -  brandingArea.width
        anchors.top: parent.top
        anchors.right: parent.right
    }

    Rectangle
    {
        id: menuArea
        height: parent.height - applicationData.Theme.BarHeight * 2
        width: 220
        color: "lightgreen"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }

    StackView
    {
        id: stackView
        height: parent.height - applicationData.Theme.BarHeight * 2
        width: parent.width -  menuArea.width
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }

    /*
    Action
    {
        id: navigateMenuAction
        icon.name: stackView.depth > 1 ? "back" : "drawer"
        onTriggered:
        {
            if (stackView.depth > 1)
            {
                stackView.pop()
            }
            else
            {
                drawer.open()
            }
        }
    }

    Action
    {
        id: openMenuAction
        icon.name: stackView.depth > 1 ? "back" : "drawer"
        onTriggered:
        {
            drawer.open()
        }
    }

    Action
    {
        id: navigateScanDevices
        icon.name: stackView.depth
        onTriggered:
        {
            applicationData.invokeSaveCurrentPage("ScanningTest.qml")
            stackView.pop()
            stackView.push("ScanningTest.qml")
        }
    }

    Action
    {
        id: navigateConnectDevices
        icon.name: stackView.depth
        onTriggered:
        {
            applicationData.invokeSaveCurrentPage("ConnectionTest.qml")
            stackView.pop()
            stackView.push("ConnectionTest.qml")
        }
    }

    Drawer
    {
        id: drawer
        width: 200 //mainView.width * 0.75
        height: mainView.height

        Column
        {
            anchors.fill: parent

            ItemDelegate
            {
                text: qsTr("Home")
                width: parent.width

                onClicked:
                {                   
                    drawer.close()
                    applicationData.invokeSaveCurrentPage("Home.qml")
                    stackView.pop()
                    stackView.push("Home.qml")
                }

                icon
                {
                    source: "../images/Home.png"
                    width: iconWidth
                    height: iconHeight
                }

                enabled:
                {
                    if(applicationData.CurrentMeterSerialNo === "")
                    {
                        return false
                    }

                    return true
                }
            }

            ItemDelegate
            {
                text: qsTr("Scanning Test")
                width: parent.width
                onClicked:
                {
                    applicationData.invokeSaveCurrentPage("ScanningTest.qml")
                    stackView.pop()
                    stackView.push("ScanningTest.qml")
                    drawer.close()
                }

                icon
                {
                    source: "../images/Scan.png"
                    width: iconWidth
                    height: iconHeight
                }
            }

            ItemDelegate
            {
                text: qsTr("Connection Test")
                width: parent.width
                onClicked:
                {
                    applicationData.invokeSaveCurrentPage("ConnectionTest.qml")
                    stackView.pop()
                    stackView.push("ConnectionTest.qml")
                    drawer.close()
                }

                icon
                {
                    source: "../images/Connect.png"
                    width: iconWidth
                    height: iconHeight
                }
            }

            ItemDelegate
            {
                text: qsTr("Trace")
                width: parent.width
                onClicked:
                {
                    applicationData.invokeSaveCurrentPage("Trace.qml")
                    stackView.pop()
                    stackView.push("Trace.qml")
                    drawer.close()
                }

                icon
                {
                    source: "../images/Trace.png"
                    width: iconWidth
                    height: iconHeight
                }
            }

            ItemDelegate
            {
                text: qsTr("Exit")
                width: parent.width
                onClicked:
                {
                    isClosing = true;
                    drawer.close();
                    applicationData.invokeExit();
                }

                icon
                {
                    source: "../images/Exit.png"
                    width: iconWidth
                    height: iconHeight
                }
            }
        }
    }
    */

    Connections
    {
        target: applicationData

        function onPageAction(pg)
        {
            if(pg === 0)
            {
                stackView.pop();
                oldPage = applicationData.invokeRetreiveLastPage()
                applicationData.invokeSaveCurrentPage(oldPage)
                stackView.push(oldPage);
            }

            if(pg === 1)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("ScanningTest.qml")
                stackView.push("ScanningTest.qml");
            }

            if(pg === 2)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("ConnectionTest.qml")
                stackView.push("ConnectionTest.qml");
            }

            if(pg === 3)
            {
                stackView.pop();
                applicationData.invokeSaveCurrentPage("Trace.qml")
                stackView.push("Trace.qml");
            }
        }
    }
}
