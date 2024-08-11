import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item
{
    id: root

    Rectangle
    {
        id: actionBar
        height: applicationData.Theme.BarHeight
        width: parent.width
        anchors.top: parent.top
        color: applicationData.Theme.BackgroundColor

        Row
        {
            spacing: 5
            anchors.rightMargin: 10
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.verticalCenter: parent.verticalCenter

            Rectangle
            {
                height: actionBar.height
                width: actionBar.height
                color: applicationData.Theme.BackgroundColor
                CustomRoundButton
                {
                    buttonSize: actionBar.height*0.66
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    accentColor: applicationData.Theme.BackgroundColor
                    imageSource:
                    {
                        if(applicationData.IsDarkTheme === true)
                        {
                            return "../images/ExportWhite.png";
                        }
                        else
                        {
                            return "../images/ExportBlack.png";
                        }
                    }
                }
            }

            Rectangle
            {
                height: actionBar.height
                width: actionBar.height
                color: applicationData.Theme.BackgroundColor
                CustomRoundButton
                {
                    buttonSize: actionBar.height*0.66
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    accentColor: applicationData.Theme.BackgroundColor
                    imageSource:
                    {
                        if(applicationData.IsDarkTheme === true)
                        {
                            return "../images/ImportWhite.png";
                        }
                        else
                        {
                            return "../images/ImportBlack.png";
                        }
                    }
                }
            }

            Rectangle
            {
                height: actionBar.height
                width: actionBar.height
                color: applicationData.Theme.BackgroundColor
                CustomRoundButton
                {
                    buttonSize: actionBar.height*0.66
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    accentColor: applicationData.Theme.BackgroundColor
                    imageSource:
                    {
                        if(applicationData.IsDarkTheme === true)
                        {
                            return "../images/AddWhite.png";
                        }
                        else
                        {
                            return "../images/AddBlack.png";
                        }
                    }
                }
            }
        }
    }
}
