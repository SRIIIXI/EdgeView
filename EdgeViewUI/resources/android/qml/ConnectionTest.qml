import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.3
import QtQuick.Layouts 1.3

Page
{
    id: connectionTestPage

    property variant availableDevicesModel :  []
    property string selectedDevice:  " "

    Component.onCompleted:
    {
        headerPanel.visible = true
        availableDevicesModel = applicationData.DeviceList
        errorLabel.text = ""
    }

    Rectangle
    {
        id: background
        width: parent.width
        height: parent.height - headerPanel.height
        anchors.top: headerPanel.bottom
        color: applicationData.Theme.BackgroundColor
    }

    Header
    {
        id:headerPanel
        headerTitle: "Discovered Devices"
        isMenuButtonVisible: true
    }

    ListView
    {
        id: deviceListView
        width: parent.width*0.90
        anchors.top:headerPanel.bottom
        anchors.topMargin: 5
        anchors.bottom: errorLabel.top
        anchors.horizontalCenter: parent.horizontalCenter
        visible: true
        spacing: 5
        clip: true
        model: availableDevicesModel
        delegate: deviceListDelegate
    }

    Component
    {
        id: deviceListDelegate

        Rectangle
        {
            id: availableDevicesItem
            width: deviceListView.width
            height: connectionTestPage.width*0.3
            radius: 5
            color: applicationData.Theme.ControlColor

            Column
            {
                id: infocol
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 20
                anchors.left: availableDevicesItem.left

                Rectangle
                {
                    id: rectData
                    height: availableDevicesItem.height
                    width:  availableDevicesItem.height*1.5
                    color: applicationData.Theme.ControlColor
                    visible: true

                    Text
                    {
                        id: deviceNamelabel
                        text: availableDevicesModel[index].DeviceName
                        font.pointSize: headerPanel.fontSizeNormal
                        font.bold: true
                        anchors.top: rectData.top
                        anchors.topMargin: rectData.height*0.1
                        color: applicationData.Theme.FontColor
                    }

                    Text
                    {
                        id: deviceAddresslabel
                        anchors.top: deviceNamelabel.bottom
                        text: availableDevicesModel[index].DeviceAddress
                        font.pointSize: headerPanel.fontSizeSmall
                        font.bold: false
                        color: applicationData.Theme.FontColor
                    }


                    Text
                    {
                        id: rssilabel
                        anchors.top: deviceAddresslabel.bottom
                        text: "Signal " + availableDevicesModel[index].RSSI
                        font.pointSize: headerPanel.fontSizeSmall
                        font.bold: false
                        color: applicationData.Theme.FontColor
                    }

                    Text
                    {
                        id: connectionStatusLabel
                        anchors.top: rssilabel.bottom
                        font.pointSize: headerPanel.fontSizeSmall
                        color:
                        {
                            if(availableDevicesModel[index].Status === "0")
                                return "red"
                            else
                                return "green"
                        }

                        font.bold:
                        {
                            if(availableDevicesModel[index].Status === "0")
                                return false
                            else
                                return true
                        }

                        elide: Label.ElideRight
                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                        text:
                        {
                            if(availableDevicesModel[index].Status === "0")
                                return "Not Connected"
                            else
                                return "Connected"
                        }
                    }
                }
            }

            Column
            {
                id: commandcol
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: availableDevicesItem.right
                anchors.rightMargin: 10

                Rectangle
                {
                    id: rectButtons
                    height: availableDevicesItem.height
                    width: (availableDevicesItem.height*0.35)*3
                    color: "transparent"

                    CustomButton
                    {
                        id: btnConnect
                        anchors.right: rectButtons.right
                        anchors.bottom: rectButtons.bottom
                        anchors.bottomMargin: rectButtons.height*0.1
                        width: (availableDevicesItem.height*0.35)*3
                        height: availableDevicesItem.height*0.35
                        isDefault: true
                        accentColor: applicationData.Theme.AccentColor
                        enabled: true
                        visible: true

                        text:
                        {
                            if(availableDevicesModel[index].Status === "0")
                                return "Connect"
                            else
                                return "Disconnect"
                        }

                        onClicked:
                        {
                            errorLabel.text = ""
                            deviceListView.enabled = false;
                            headerPanel.isMenuButtonVisible = false
                            if(availableDevicesModel[index].Status === "0")
                            {
                                applicationData.invokeConnectDevice(availableDevicesModel[index].DeviceAddress)
                            }
                            else
                            {
                                if(availableDevicesModel[index].Status === "1")
                                {
                                    applicationData.invokeDisconnectDevice(availableDevicesModel[index].DeviceAddress)
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Label
    {
        id: errorLabel
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
        text: ""
        color: "red"
        wrapMode: "Wrap"
        anchors.topMargin: 5
        anchors.bottomMargin: 5
    }

    Connections
    {
        target: applicationData

        function onDeviceAction()
        {
            availableDevicesModel = applicationData.DeviceList
            deviceListView.enabled = true;
            headerPanel.isDeviceNameVisible = true;
            headerPanel.isMenuButtonVisible = true
        }

        function onDeviceMessage(fl, str)
        {
            if(fl === true)
            {
                errorLabel.color = "green"
            }
            else
            {
                errorLabel.color = "red"
            }

            errorLabel.text = str
        }
    }
}


