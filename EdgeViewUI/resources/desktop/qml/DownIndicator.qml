import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item
{
    id: root
    property string backgroudColor: "transparent"

    Rectangle
    {
        id: rect
        anchors.fill: parent
        color: backgroudColor
        Canvas
        {
            anchors.fill:parent

            onPaint:
            {
                var context = getContext("2d");

                // the triangle
                context.beginPath();
                context.moveTo(0, 0);
                context.lineTo(rect.width, 0);
                context.lineTo(rect.width/2, rect.height);
                context.closePath();

                // the fill color
                context.fillStyle = "red";
                context.fill();
            }
        }
    }
}
