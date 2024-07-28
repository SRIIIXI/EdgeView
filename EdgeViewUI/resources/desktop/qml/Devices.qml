import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import Qt.labs.qmlmodels

Item
{
    id: root

    property variant deviceModel: []

    signal editRequested(int mode);

    Component.onCompleted:
    {
        deviceModel = applicationData.DeviceList
    }

    Rectangle
    {
        color: applicationData.Theme.BackgroundColor
        anchors.fill: parent
    }

    Rectangle
    {
        id: tableHeader
        height: applicationData.Theme.BarHeight*0.75
        width: parent.width
        color: applicationData.Theme.BackgroundColor

        Rectangle
        {
            border.color: "lightgrey"//applicationData.Theme.ControlColor
            height: 1
            width: parent.width
            anchors.top: tableHeader.top
        }

        Rectangle
        {
            border.color: "lightgrey"//applicationData.Theme.ControlColor
            height: 1
            width: parent.width
            anchors.bottom: tableHeader.bottom
        }

        CheckBox
        {
            id: mark
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 10
            Material.accent: applicationData.Theme.AccentColor
            Material.theme:
            {
                if(applicationData.IsDarkTheme === true)
                {
                    return Material.Dark;
                }
                else
                {
                    return Material.Light;
                }
            }
        }

        Label
        {
            id: name
            text: "Device"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: mark.right
            width: parent.width*0.20
            color: applicationData.Theme.FontColor
        }

        Label
        {
            id: serialno
            text: "Serial No"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: name.right
            width: parent.width*0.20
            color: applicationData.Theme.FontColor
        }

        Label
        {
            id: hardwareid
            text: "Hardware Id"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: serialno.right
            width: parent.width*0.20
            color: applicationData.Theme.FontColor
        }

        Label
        {
            id: devicetype
            text: "Type"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: hardwareid.right
            width: parent.width*0.15
            color: applicationData.Theme.FontColor
        }

        Label
        {
            id: devicestatus
            text: "Status"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: devicetype.right
            width: parent.width*0.20
            color: applicationData.Theme.FontColor
        }
    }

    ListView
    {
        id: deviceListView
        height: parent.height - tableHeader.height
        width: parent.width
        anchors.top: tableHeader.bottom
        visible: true
        spacing: 0
        clip: true
        model: deviceModel
        delegate: deviceListDelegate
    }

    Component
    {
        id: deviceListDelegate

        Rectangle
        {
            id: deviceItem
            width: deviceListView.width
            height: tableHeader.height
            radius: 0
            color: applicationData.Theme.BackgroundColor

            CheckBox
            {
                id: markItem
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                Material.accent: applicationData.Theme.AccentColor
                Material.theme:
                {
                    if(applicationData.IsDarkTheme === true)
                    {
                        return Material.Dark;
                    }
                    else
                    {
                        return Material.Light;
                    }
                }
            }

            Label
            {
                id: nameItem
                text: applicationData.DeviceList[index].DeviceName
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: markItem.right
                width: parent.width*0.20
                color: applicationData.Theme.FontColor
            }

            Label
            {
                id: serialnoItem
                text: applicationData.DeviceList[index].SerialNo
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: nameItem.right
                width: parent.width*0.20
                color: applicationData.Theme.FontColor
            }

            Label
            {
                id: hardwareidItem
                text: applicationData.DeviceList[index].HardwareId
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: serialnoItem.right
                width: parent.width*0.20
                color: applicationData.Theme.FontColor
            }

            Label
            {
                id: typeItem
                text: applicationData.DeviceList[index].Type
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: hardwareidItem.right
                width: parent.width*0.15
                color: applicationData.Theme.FontColor
            }

            Label
            {
                id: statusItem
                text: applicationData.DeviceList[index].Status
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: typeItem.right
                width: parent.width*0.20
                color: applicationData.Theme.FontColor
            }

            ToolButton
            {
                id: editBtnItem
                height: tableHeader.height*0.75
                width: tableHeader.height*0.75
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 5
                anchors.right: deleteBtnItem.left

                icon.source:
                {

                    if(applicationData.IsDarkTheme === true)
                    {
                        return "../images/EditWhite.png"
                    }
                    else
                    {
                        return "../images/EditBlack.png"
                    }
                }

                icon.color: "transparent"
                icon.height: tableHeader.height*0.75
                icon.width: tableHeader.height*0.75

                background: Rectangle
                {
                    color: applicationData.Theme.BackgroundColor
                }

                onClicked:
                {
                    editDevice(index);
                }
            }

            ToolButton
            {
                id: deleteBtnItem
                height: tableHeader.height*0.75
                width: tableHeader.height*0.75
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 10
                anchors.right: parent.right

                icon.source:
                {

                    if(applicationData.IsDarkTheme === true)
                    {
                        return "../images/DeleteWhite.png"
                    }
                    else
                    {
                        return "../images/DeleteBlack.png"
                    }
                }

                icon.color: "transparent"
                icon.height: tableHeader.height*0.75
                icon.width: tableHeader.height*0.75

                background: Rectangle
                {
                    color: applicationData.Theme.BackgroundColor
                }
            }
        }
    }

    function deleteDevice(index)
    {
    }

    function editDevice(index)
    {
        editRequested(index);
    }

    Connections
    {
        target: applicationData

        function onDeviceAction()
        {
            deviceModel = applicationData.DeviceList
        }
    }
}
