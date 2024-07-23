import QtQuick 2.0
import QtQuick.Controls.Material 2.3

Rectangle
{
    id: root
    property string imageSource: ''
    property int buttonSize: 25
    property string accentColor: "dodgerblue"
    signal clicked();

    width: buttonSize
    height: buttonSize
    border.color: accentColor
    border.width: 1
    radius:       buttonSize*0.5
    opacity:      enabled  &&  !mouseArea.pressed? 1: 0.3

    color:accentColor

    Image
    {
        id: name
        anchors.centerIn: parent
        height: buttonSize*0.66
        width: buttonSize*0.66
        source: imageSource
    }

    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        onClicked:  root.clicked()
    }
}
