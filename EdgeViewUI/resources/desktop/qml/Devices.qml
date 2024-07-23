import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3


Item
{
    id: root

    CustomTable
    {
        headerColor: applicationData.Theme.ControlColor
        fontColor: applicationData.Theme.FontColor
        anchors.fill: parent
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
