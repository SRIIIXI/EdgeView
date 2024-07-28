import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.3
import QtQuick.Layouts 1.15

Rectangle
{
    id: headerID

    height: applicationData.Theme.BarHeight
    width: parent.width
    color: applicationData.Theme.BackgroundColor

    property string headerTitle: ""

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
    }

    Label
    {
        id: fontlabel
        text: ""
    }

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
        font.pointSize: fontSizeLarge
    }

    ToolButton
    {
        id: backBtnID
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        height: parent.height
        width: parent.height
        visible: true
        icon.source :"../images/EdgeView.png"
        icon.color: "transparent"
        icon.height: parent.height*0.5
        icon.width: parent.height*0.5

        background: Rectangle
        {
            color: applicationData.Theme.BackgroundColor
        }
    }
}
