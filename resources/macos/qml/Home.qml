import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.3
import QtQuick.Layouts 1.3

Page
{
    id: homePage

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
        headerTitle: "Home"
        isMenuButtonVisible: true
        isDeviceNameVisible: true
    }

    ScrollView
    {
        width: parent.width
        height: parent.height - headerPanel.height
        anchors.top: headerPanel.bottom
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
    }
}
