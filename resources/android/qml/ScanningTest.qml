import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.3
import QtQuick.Layouts 1.3

Page
{
    id: scanningTestPage

    Rectangle
    {
        id: background
        width: parent.width
        height: parent.height - headerPanel.height
        anchors.top: headerPanel.bottom
        color: applicationData.Theme.BackgroundColor
    }

    Label
    {
        id: fontlabel
        text: ""
    }

    Header
    {
        id:headerPanel
        headerTitle: "Scanning Test"
        isMenuButtonVisible: true
        isDeviceNameVisible: true
    }

    ScrollView
    {
        width: parent.width
        height: parent.height - headerPanel.height - scanCommandRect.height
        anchors.top: headerPanel.bottom
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn


        TextArea
        {
            id: scanResult
            readOnly: true
            anchors.fill: parent
            font.pointSize: fontlabel.font.pointSize -  2.5
            color: applicationData.Theme.FontColor
            text: applicationData.ScanLog
        }
    }

    Rectangle
    {
        id: scanCommandRect
        width: scanningTestPage.width
        height: scanningTestPage.width*0.2
        radius: 5
        color: applicationData.Theme.ControlColor
        anchors
        {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }

        CustomButton
        {
            id: btnScan
            text: "Scan"
            height: parent.width*0.125
            width: (parent.width*0.2)*2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            textAlignment: Text.ElideRight
            isDefault: true
            accentColor: applicationData.Theme.AccentColor
            onClicked:
            {
                headerPanel.isMenuButtonVisible = false
                applicationData.invokeScan();
                enabled = false;
            }
        }
    }

    Connections
    {
        target: applicationData

        function onScanFinished()
        {
            headerPanel.isMenuButtonVisible = true
            btnScan.enabled = true;
        }
    }
}
