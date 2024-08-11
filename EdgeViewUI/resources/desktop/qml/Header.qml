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

    Image
    {
        id: backBtnID
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        height: parent.height*0.9
        visible: true
        source :"../images/EdgeView.png"
        fillMode: Image.PreserveAspectFit
        antialiasing: true
    }
}
