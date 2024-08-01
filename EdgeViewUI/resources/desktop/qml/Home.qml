import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item
{
    id: root

    Rectangle
    {
        id: background
        anchors.fill: parent
        color: applicationData.Theme.BackgroundColor
    }

    Label
    {
       id: dummy
       text: "Home"
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.verticalCenter: parent.verticalCenter
       color: applicationData.Theme.FontColor
    }
}
