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

    color: normalColor

    Row
    {
        width: menuWidth
        height: menuHeight
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 15

        Rectangle
        {
            id: indicator
            height: menuHeight
            width: menuHeight*0.2
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
        }

        Rectangle
        {
            height: menuHeight
            width: menuHeight
            color: normalColor
            Image
            {
                source: menuIconSource
                width: menuHeight*0.5
                height: menuHeight*0.5
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                antialiasing: true
            }
        }

        Rectangle
        {
            height: menuHeight
            width: menuWidth*0.8 - menuHeight
            color: normalColor

            Text
            {
                text: root.text
                elide: textAlignment
                color:
                {
                    if(isActive === true)
                    {
                        return activeColor
                    }
                    else
                    {
                        return textColor
                    }
                }

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.bold: false
            }
        }
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
