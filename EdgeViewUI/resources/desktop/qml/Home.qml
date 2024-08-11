import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item
{
    id: root

    Rectangle
    {
        id: background
        anchors.fill: parent
        color: applicationData.Theme.BackgroundColor

        Rectangle
        {
            id: topLeft
            width: parent.width*0.3
            height: parent.height*0.5 - separator.height/4
            anchors.top : parent.top
            anchors.left: parent.left
            color: "transparent"

            CustomTrendCard
            {
                id: bandwidth
                width: parent.width
                height: parent.width*0.4
                trendName: "Bandwidth"
                trendValue: "25 MBPS"
                trendValueChange: "12.5%"
                isDown: false
            }

            CustomTrendCard
            {
                id: faults
                width: parent.width
                height: parent.width*0.4
                anchors.top:  bandwidth.bottom
                trendName: "Sensor Faults"
                trendValue: "29"
                trendValueChange: "3%"
                isDown: true
            }
        }

        Rectangle
        {
            id: topCentre
            width: parent.width*0.4
            height: parent.height*0.5 - separator.height/2
            anchors.top : parent.top
            anchors.left: topLeft.right
            color: applicationData.Theme.BackgroundColor

            CircularProgressBar
            {
                anchors.fill: parent
                size: topCentre.width*0.85
                lineWidth: topCentre.width*0.075
                value: 50
                title: "Average Uptime"
                primaryColor: applicationData.Theme.AccentColor
                secondaryColor: applicationData.Theme.AccentLowColor
            }
        }

        Rectangle
        {
            id: topRight
            width: parent.width*0.3
            height: parent.height*0.5 - separator.height/4
            anchors.top : parent.top
            anchors.left: topCentre.right
            color: "transparent"

            CustomTrendCard
            {
                id: activeSessions
                width: parent.width
                height: parent.width*0.4
                trendName: "Active"
                trendValue: "4567"
                trendValueChange: "6%"
                isDown: false
            }

            CustomTrendCard
            {
                id: lowbattery
                width: parent.width
                height: parent.width*0.4
                anchors.top:  activeSessions.bottom
                trendName: "Low Battery"
                trendValue: "64"
                trendValueChange: "4%"
                isDown: true
            }
        }

        Rectangle
        {
            id: separator
            width: parent.width
            height: applicationData.Theme.BarHeight
            anchors.top: topCentre.bottom
            color: applicationData.Theme.BackgroundColor
        }

        Rectangle
        {
            id: bottomLeft
            width: parent.width*0.5
            height: parent.height*0.5 - separator.height/2
            anchors.bottom : parent.bottom
            anchors.left: parent.left
            color: applicationData.Theme.BackgroundColor

            CustomBarChart
            {
                width: parent.width*0.95
                height: parent.height*0.95
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                title:  'Telemetry and Alarms - Last 24 Hours'
                yLabel: 'Hourly Count'
                xLabel: 'Spending Category'
                color1: applicationData.Theme.AccentColor
                color2: applicationData.Theme.StandoutColor

                points: [
                    {x: '03',  y1: 1205.7, y2: 12.0},
                    {x: '06',  y1: 1051.8, y2: 10.0},
                    {x: '09',  y1: 1200.3, y2: 65.0},
                    {x: '12',  y1: 1200.2, y2: 27.0},
                    {x: '15',  y1: 1160.6, y2: 16.6},
                    {x: '18',  y1: 1085.7, y2: 11.0},
                    {x: '21',  y1: 1102.3, y2: 10.3},
                    {x: '24',  y1: 1085.0, y2: 65.6},
                ]
            }
        }

        Rectangle
        {
            id: bottomRight
            width: parent.width*0.5
            height: parent.height*0.5 - separator.height/2
            anchors.bottom : parent.bottom
            anchors.right: parent.right
            color: applicationData.Theme.BackgroundColor

            CustomLineChart
            {
                width: parent.width*0.95
                height: parent.height*0.95
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter

                title:  'Pendulum Position versus Time'
                yLabel: 'position (degrees)'
                xLabel: 'time (s)'
                color1: applicationData.Theme.AccentColor
                color2: applicationData.Theme.StandoutColor

                Component.onCompleted:
                { // sine wave
                    var positions = [], N = 100, T = 1

                    positions.push( {x1: 0, y1: 0, x2: 9, y2: 1} )
                    positions.push( {x1: 2, y1: 2, x2: 7, y2: 3} )
                    positions.push( {x1: 4, y1: 4, x2: 5, y2: 5} )
                    positions.push( {x1: 6, y1: 6, x2: 3, y2: 7} )
                    positions.push( {x1: 8, y1: 8, x2: 1, y2: 9} )

                    points = positions
                }
            }
        }
    }
}
