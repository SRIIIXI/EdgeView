import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQuick.Effects

Item
{
    id: root

    onHeightChanged:
    {
        if(height >= width)
        {
            uptimeGraph.size = topCentre.width*0.85
            monitoreddevice.width = topRight.width*0.95
            monitoreddevice.height = topRight.width*0.95
        }

        if(width > height)
        {
            uptimeGraph.size = topCentre.height*0.85
            monitoreddevice.width = topRight.height*0.95
            monitoreddevice.height = topRight.height*0.95
        }
    }

    Rectangle
    {
        id: marginBar
        width: parent.width
        height: applicationData.Theme.BarHeight
        color: applicationData.Theme.BackgroundColor
    }

    Rectangle
    {
        id: background
        width: parent.width
        height: parent.height - marginBar.height
        anchors.top : marginBar.bottom
        color: applicationData.Theme.BackgroundColor

        Rectangle
        {
            id: topLeft
            width: parent.width*0.27
            height: parent.height*0.5 - separator.height/2 - marginBar.height
            anchors.top : parent.top
            anchors.left: parent.left
            color: "transparent"

            CustomTrendCard
            {
                id: bandwidth
                width: parent.width
                height: topLeft.height*0.25
                trendName: "Bandwidth"
                trendValue: "25 MBPS"
                trendValueChange: "12.5%"
                imageSource: "../images/Bandwidth.png"
                fontColor: applicationData.Theme.FontColor
                isDown: false
            }

            CustomTrendCard
            {
                id: faults
                width: parent.width
                height: topLeft.height*0.25
                anchors.top:  bandwidth.bottom
                trendName: "Sensor Faults"
                imageSource: "../images/Fault.png"
                trendValue: "29"
                trendValueChange: "3%"
                fontColor: applicationData.Theme.FontColor
                isDown: true
            }

            CustomTrendCard
            {
                id: activeSessions
                width: parent.width
                height: topLeft.height*0.25
                anchors.top:  faults.bottom
                trendName: "Avg. Uptime"
                trendValue: "4567"
                trendValueChange: "6%"
                imageSource: "../images/Active.png"
                fontColor: applicationData.Theme.FontColor
                isDown: false
            }

            CustomTrendCard
            {
                id: lowbattery
                width: parent.width
                height: topLeft.height*0.25
                anchors.top:  activeSessions.bottom
                trendName: "Low Battery"
                trendValue: "64"
                trendValueChange: "4%"
                imageSource: "../images/Battery.png"
                fontColor: applicationData.Theme.FontColor
                isDown: true
            }
        }

        Rectangle
        {
            id: topCentre
            width: parent.width*0.35
            height: parent.height*0.5 - separator.height/2  - marginBar.height
            anchors.top : parent.top
            anchors.left: topLeft.right
            color: applicationData.Theme.BackgroundColor

            CircularProgressBar
            {
                id: uptimeGraph
                anchors.fill: parent
                size: topCentre.width*0.85
                lineWidth: topCentre.width*0.075
                value: 85
                title: "Active Devices"
                primaryColor: applicationData.Theme.AccentColor
                secondaryColor: applicationData.Theme.AccentLowColor
            }
        }

        Rectangle
        {
            id: topRight
            width: parent.width*0.38
            height: parent.height*0.5 - separator.height/2  - marginBar.height
            anchors.top : parent.top
            anchors.left: topCentre.right
            color: "transparent"

            CustomLineChart
            {
                id: monitoreddevice
                width: parent.width*0.95
                height: parent.width*0.95
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter

                title:  'Monitored Device'
                yLabel: 'position (degrees)'
                xLabel: 'time (s)'
                color1: applicationData.Theme.AccentColor
                color2: applicationData.Theme.StandoutColor

                Component.onCompleted:
                {
                    var positions = [], N = 100, T = 1

                    positions.push( {x1: 0, y1: 0, x2: 0, y2: 1} )
                    positions.push( {x1: 2, y1: 2, x2: 2, y2: 3} )
                    positions.push( {x1: 3, y1: 4, x2: 3, y2: 5} )
                    positions.push( {x1: 4, y1: 6, x2: 4, y2: 4} )
                    positions.push( {x1: 5, y1: 4, x2: 5, y2: 3} )

                    points = positions
                }
            }
        }

        Rectangle
        {
            id: separator
            width: parent.width
            height: applicationData.Theme.BarHeight/4
            anchors.top: topCentre.bottom
            color: applicationData.Theme.BackgroundColor
        }

        Rectangle
        {
            id: bottom
            width: parent.width
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
                    {x: '02',  y1: 1205.7, y2: 12.0},
                    {x: '04',  y1: 1051.8, y2: 10.0},
                    {x: '06',  y1: 1200.3, y2: 65.0},
                    {x: '08',  y1: 1200.2, y2: 27.0},
                    {x: '10',  y1: 1160.6, y2: 16.6},
                    {x: '12',  y1: 1085.7, y2: 11.0},
                    {x: '14',  y1: 1102.3, y2: 10.3},
                    {x: '16',  y1: 1085.0, y2: 65.6},
                    {x: '18',  y1: 1205.7, y2: 12.0},
                    {x: '20',  y1: 1051.8, y2: 10.0},
                    {x: '22',  y1: 1200.3, y2: 65.0},
                    {x: '24',  y1: 1102.3, y2: 10.3},
                ]
            }
        }
    }
}
