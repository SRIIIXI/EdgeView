import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item
{
    id: root

    Rectangle
    {
        anchors.fill: parent
        color: "transparent"
        property string imageSource: "../images/Bandwidth.png"

        Rectangle
        {
            id: imgArea
            height: parent.height
            width: parent.width*0.25
            anchors.left: parent.left
            color: "transparent"

            Image
            {
                id: name
                width: parent.width*0.75
                height: parent.width*0.75
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                source: imageSource
            }

            CheckBox
            {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
            }
        }

        Rectangle
        {
            id: infoArea
            anchors.left: imgArea.right
            height: parent.height
            width: parent.width -  imgArea.width
            color: "transparent"

            Rectangle
            {
                width: parent.width
                height: parent.height/2
                anchors.top: parent.top
                color: "transparent"

                Text
                {
                    text: "Bandwidth"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle
            {
                width: parent.width
                height: parent.height/2
                anchors.bottom: parent.bottom
                color: "transparent"

                Text
                {
                    text: "28 MBPS"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }
}
