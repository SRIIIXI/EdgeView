import QtQuick 2.0
import QtQuick.Controls;
import QtQuick.Controls.Material;

Item
{
    id: root

    // public
    property variant headerModel: []
    property variant dataModel: []

    property int currentRow: 0
    property int headerHeight: 20
    property int rowHeight: 10
    property string headerColor: "dodgerblue"
    property string fontColor: "black"
    property string rowColor: "lightgrey"
    property string accentColor: "dodgerblue"
    property bool isDarkTheme: true

    signal clicked(int row);

    // private
    width: 500;
    height: 200

    Rectangle
    {
        id: header

        width: parent.width;
        height: headerHeight
        color: headerColor
        radius: 0

        ListView
        {
            id: listHeader
            // header
            anchors.fill: parent
            orientation: ListView.Horizontal
            interactive: false

            model: headerModel

            delegate: Item
            {
                // cell
                width: modelData.width * root.width;
                height: header.height

                CheckBox
                {
                    id: selectMark
                    anchors.verticalCenter: parent.verticalCenter
                    visible:
                    {
                        if(index === 0)
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    onCheckedChanged:
                    {
                        root.currentRow = index;
                        root.clicked(index);
                    }
                    Material.accent: accentColor
                    Material.theme:
                    {
                        if(isDarkTheme === true)
                        {
                            return Material.Dark;
                        }
                        else
                        {
                            return Material.Light;
                        }
                    }
                }

                Text
                {
                    x: 0.03 * root.width
                    text: modelData.text
                    anchors.left: selectMark.right
                    anchors.verticalCenter: parent.verticalCenter
                    color: fontColor
                    font.bold: true
                }
            }
        }
    }

    Rectangle
    {
        width: parent.width;
        height: parent.height - headerHeight
        anchors.top: header.bottom
        color: rowColor
    }

    ListView
    {
        id: listRows
        // data
        anchors
        {
            fill: parent;
            topMargin: header.height
        }

        interactive: contentHeight > height
        clip: true

        model: dataModel

        delegate: Item
        {
            // row
            width: root.width;
            height: header.height
            //opacity: !mouseArea.pressed? 1: 0.3 // pressed state

            property int     row:     index     // outer index
            property variant rowData: modelData // much faster than listView.model[row]

            Row
            {
                id: tableRow
                anchors.fill: parent

                Repeater
                {
                    id: cell
                    // index is column
                    model: rowData // headerModel.length

                    delegate: Item
                    {
                        // cell
                        width: headerModel[index].width * root.width;
                        height: header.height

                        CheckBox
                        {
                            id: selectMarkRow
                            anchors.verticalCenter: parent.verticalCenter
                            visible:
                            {
                                if(index === 0)
                                {
                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            }
                            onCheckedChanged:
                            {
                                root.currentRow = index;
                                root.clicked(index);
                            }
                            Material.accent: accentColor
                            Material.theme:
                            {
                                if(isDarkTheme === true)
                                {
                                    return Material.Dark;
                                }
                                else
                                {
                                    return Material.Light;
                                }
                            }
                        }

                        Text
                        {
                            x: 0.03 * root.width
                            text: modelData
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: selectMarkRow.right
                            color: fontColor

                            MouseArea
                            {
                                anchors.fill: parent
                                onClicked:
                                {
                                    root.currentRow = index;
                                    root.clicked(index);
                                }
                            }
                        }
                    }
                }
            }
        }

        CustomScrollBar{}
    }
}

