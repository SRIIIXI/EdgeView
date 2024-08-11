import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.3
import QtQuick.Layouts 1.15

Item
{
    id: root

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
}
