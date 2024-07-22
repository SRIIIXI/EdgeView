import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Page
{
    id: homePage

    Rectangle
    {
        id: background
        anchors.fill: parent
        color: applicationData.Theme.BackgroundColor
    }

    ScrollView
    {
        anchors.fill: parent
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        // Label
        // {
        //    id: dummy
        //    text: "Devices"
        //    anchors.horizontalCenter: parent.horizontalCenter
        //    anchors.verticalCenter: parent.verticalCenter
        //    color: applicationData.Theme.FontColor
        // }

        CustomTable
        {
            headerColor: applicationData.Theme.ControlColor
            fontColor: applicationData.Theme.FontColor
            width: parent.width
            height: parent.height
            headerModel: [ // widths must add to 1
                {text: 'Color',         width: 0.5},
                {text: 'Hexadecimal',   width: 0.5},
            ]

            dataModel: [
                ['Red',   '#ff0000'],
                ['Green', '#00ff00'],
                ['Blue',  '#0000ff'],
            ]

            onClicked: print('onClicked', currentRow)
        }
    }
}
