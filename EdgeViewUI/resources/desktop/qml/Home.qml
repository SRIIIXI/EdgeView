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

        //Label
        //{
        //   id: dummy
        //   text: "Home"
        //   anchors.horizontalCenter: parent.horizontalCenter
        //   anchors.verticalCenter: parent.verticalCenter
        //   color: applicationData.Theme.FontColor
        //}

        CustomTable
        {
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
