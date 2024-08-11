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

        Rectangle
        {
            id: topLeft
            width: parent.width*0.3
            height: parent.height*0.5
            anchors.top : parent.top
            anchors.left: parent.left
            color: "red"
        }

        Rectangle
        {
            id: topCentre
            width: parent.width*0.4
            height: parent.height*0.5
            anchors.top : parent.top
            anchors.left: topLeft.right
            color: applicationData.Theme.BackgroundColor

            CircularProgressBar
            {
                anchors.fill: parent
                size: topCentre.width*0.85
                lineWidth: topCentre.width*0.075
                value: 50
                primaryColor: applicationData.Theme.AccentColor
                secondaryColor: applicationData.Theme.AccentLowColor
            }
        }

        Rectangle
        {
            id: topRight
            width: parent.width*0.3
            height: parent.height*0.5
            anchors.top : parent.top
            anchors.left: topCentre.right
            color: "green"
        }

        Rectangle
        {
            id: bottomLeft
            width: parent.width*0.5
            height: parent.height*0.5
            anchors.bottom : parent.bottom
            anchors.left: parent.left
            color: "orange"
        }

        Rectangle
        {
            id: bottomRight
            width: parent.width*0.5
            height: parent.height*0.5
            anchors.bottom : parent.bottom
            anchors.right: parent.right
            color: "yellow"
        }
    }
}
