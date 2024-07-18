import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Page
{
    id: homePage

    Rectangle
    {
        id: background
        width: parent.width
        height: parent.height //- headerPanel.height
        anchors.top:  parent.top // headerPanel.bottom
        color: "grey" //applicationData.Theme.BackgroundColor

        ScrollView
        {
            anchors.fill: parent
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        }
    }

    //Label
    //{
    //    id: fontlabel
    //    text: ""
    //}

    //Header
    //{
    //    id:headerPanel
    //    headerTitle: "Home"
    //    isMenuButtonVisible: true
    //    isDeviceNameVisible: true
    //}

    //ScrollView
    //{
    //    width: parent.width
    //    height: parent.height - headerPanel.height
    //    anchors.top: headerPanel.bottom
    //    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
    //    ScrollBar.vertical.policy: ScrollBar.AlwaysOn
    //}
}
