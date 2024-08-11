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

    FontSizer
    {
        id: fontsizer
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
        font.pointSize: fontsizer.fontSizeLarge
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
