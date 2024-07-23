import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item
{
    id: root

    CustomTable
    {
        headerColor: applicationData.Theme.ControlLowColor
        fontColor: applicationData.Theme.FontColor
        rowColor: applicationData.Theme.BackgroundColor
        headerHeight: applicationData.Theme.BarHeight*0.66
        anchors.fill: parent
        headerModel: [ // widths must add to 1
            {text: 'Device',         width: 0.33},
            {text: 'Serial No',   width: 0.33},
            {text: 'Harware Id',   width: 0.33},
        ]

        dataModel: [
            ['Router',   'GW0001111', 'AE:78:90:CE:65:FF'],
            ['Energy Meter', 'EM888777', '00:AF:DA:6C:FF:0A'],
            ['Bluetooth Scanner',  'BTS444555', '03:66:ED:AB:C2:D1'],
        ]

        onClicked: print('onClicked', currentRow)
    }
}
