import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.15

Rectangle
{
    id: headerID

    height: parent.width*0.25
    width: parent.width

    property string headerTitle: ""

    property bool isMenuButtonVisible: true
    property bool isDeviceNameVisible: true

    property double fontSizeNormal: fontlabel.font.pointSize
    property double fontSizeSmall: fontlabel.font.pointSize -  2.5
    property double fontSizeTiny: fontlabel.font.pointSize - 5.0
    property double fontSizeBig: fontlabel.font.pointSize +  2.5
    property double fontSizeLarge: fontlabel.font.pointSize + 5.0

    Component.onCompleted:
    {
        fontSizeNormal = fontlabel.font.pointSize
        fontSizeSmall = fontlabel.font.pointSize -  2.5
        fontSizeTiny = fontlabel.font.pointSize - 5.0
        fontSizeBig = fontlabel.font.pointSize +  2.5
        fontSizeLarge = fontlabel.font.pointSize + 5.0

        progressAnimator.visible = true
    }

    Label
    {
        id: fontlabel
        text: ""
    }

    Rectangle
    {
        id: titleRect
        width: parent.width
        height: headerID.height * 0.6
        color: applicationData.Theme.BackgroundColor

        Label
        {
            text: headerTitle
            font.bold: false
            color: applicationData.Theme.FontColor
            elide: Label.ElideRight
            verticalAlignment: Qt.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
            font.pointSize: fontSizeBig
        }

        ToolButton
        {
            id: backBtnID
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            height: titleRect.height
            width: titleRect.height
            visible: isMenuButtonVisible

            icon.source :
            if(applicationData.IsDarkTheme === true)
            {
                return "../images/Users.png";
            }
            else
            {
                return "../images/Users.png";
            }

            icon.color: "transparent"
            icon.height: titleRect.height*0.5
            icon.width: titleRect.height*0.5

            background: Rectangle
            {
                color: applicationData.Theme.BackgroundColor
            }
        }
    }

    Rectangle
    {
        id: infoRect
        width: parent.width
        height: headerID.height * 0.4
        anchors.top: titleRect.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        color: applicationData.Theme.BackgroundColor

        Rectangle
        {
            id: infoRectInterior
            height: parent.height
            width: parent.width*0.94
            anchors.horizontalCenter: parent.horizontalCenter
            color: applicationData.Theme.BackgroundColor

            Text
            {
                color: applicationData.Theme.FontColor
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                text: applicationData.CurrentDeviceAddress
                font.pointSize: fontSizeSmall
                visible: isDeviceNameVisible
            }

            BusyIndicator
            {
                id: progressAnimator
                height: infoRect.height*0.85
                width: infoRect.height*0.85
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: infoRectInterior.right
                anchors.rightMargin: 0
                running: true

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
        }
    }

    Connections
    {
        target: applicationData

        function onProgressIndicatorsOff()
        {
            progressAnimator.visible = false;
        }

        function onProgressIndicatorsOn()
        {
            progressAnimator.visible = true;
        }
    }
}
