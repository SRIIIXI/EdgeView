import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.3
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

    signal menuButtonClicked();

    Component.onCompleted:
    {
        fontSizeNormal = fontlabel.font.pointSize
        fontSizeSmall = fontlabel.font.pointSize -  2.5
        fontSizeTiny = fontlabel.font.pointSize - 5.0
        fontSizeBig = fontlabel.font.pointSize +  2.5
        fontSizeLarge = fontlabel.font.pointSize + 5.0

        progressAnimator.visible = false
        connectionStatusIcon.visible = false
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

        ToolButton
        {
            id: backBtnID            
            anchors.verticalCenter: parent.verticalCenter
            height: titleRect.height
            width: titleRect.height
            visible: isMenuButtonVisible

            onClicked:
            {
                menuButtonClicked();
            }

            action:
            {
                openMenuAction
            }

            icon.source :
            if(applicationData.IsDarkTheme === true)
            {
                return "../images/MenuWhite.png";
            }
            else
            {
                return "../images/MenuBlack.png";
            }

            icon.color: "transparent"
            icon.height: titleRect.height*0.5
            icon.width: titleRect.height*0.5

            background: Rectangle
            {
                color: applicationData.Theme.BackgroundColor
            }
        }

        Label
        {
            text: headerTitle
            font.bold: true
            color: applicationData.Theme.FontColor
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: fontSizeBig
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

            Image
            {
                id: connectionStatusIcon
                height: infoRectInterior.height*0.6
                width: infoRectInterior.height*0.6
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source : "../images/GreenDot.png"
                visible: isConnectionIndicatorVisible
            }

            Text
            {
                color: applicationData.Theme.FontColor
                anchors.horizontalCenter: parent.horizontalCenter
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

        function onNetworkIndicatorsOff()
        {
            connectionStatusIcon.visible = false
        }

        function onNetworkIndicatorsOn()
        {
            connectionStatusIcon.visible = true
        }
    }
}
