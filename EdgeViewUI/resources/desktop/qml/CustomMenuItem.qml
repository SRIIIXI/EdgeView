import QtQuick 2.0
import QtQuick.Controls.Material 2.3

Rectangle
{
    id: root
    property string text: 'text'
    property int menuWidth: 75
    property int menuHeight: 25
    property string textColor: "black"
    property string activeColor: "dodgerblue"
    property string normalColor: "lightgrey"
    property string menuIconSource: "dodgerblue"
    property bool isActive: true
    property int textAlignment: Text.ElideNone
    signal clicked();

    width: menuWidth
    height: menuHeight
    radius:   0
    opacity:  enabled  &&  !mouseArea.pressed? 1: 0.3

    color:
    {
        if(isActive === true)
        {
            return activeColor
        }
        else
        {
            return normalColor
        }
    }

    Image
    {
        source: menuIconSource
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        width: parent.height*0.75
        height: parent.height*0.75
    }

    Text
    {
        text: root.text
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: menuIconSource.right
        elide: textAlignment
        color: textColor
    }

    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        onClicked:
        {
            isActive = true
            root.clicked()
        }
    }
}
