import QtQuick 2.0

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

                Text
                {
                    x: 0.03 * root.width
                    text: modelData.text
                    anchors.verticalCenter: parent.verticalCenter
                    color: fontColor
                    font.bold: true
                }
            }
        }
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
            opacity: !mouseArea.pressed? 1: 0.3 // pressed state

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

                        Text
                        {
                            x: 0.03 * root.width
                            text: modelData
                            anchors.verticalCenter: parent.verticalCenter
                            //font.pixelSize: 0.06 * root.width
                            color: applicationData.Theme.FontColor
                        }
                    }
                }
            }

            MouseArea
            {
                id: mouseArea
                anchors.fill: parent
                onClicked:
                {
                    root.currentRow = row;
                    root.clicked(tableRow.index)
                }
            }
        }

        CustomScrollBar{}
    }
}

