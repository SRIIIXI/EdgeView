import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item
{
    id: root

    Rectangle
    {
        id: navigationBar
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
                height: navigationBar.height
                width: navigationBar.height
                color: applicationData.Theme.BackgroundColor
                CustomRoundButton
                {
                    buttonSize: navigationBar.height*0.66
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    accentColor: applicationData.Theme.BackgroundColor
                    imageSource:
                    {
                        if(applicationData.IsDarkTheme === true)
                        {
                            return "../images/LeftWhite.png";
                        }
                        else
                        {
                            return "../images/LeftBlack.png";
                        }
                    }
                }
            }

            Rectangle
            {
                height: navigationBar.height
                width: navigationBar.height
                color: applicationData.Theme.BackgroundColor

                CustomRoundButton
                {
                    buttonSize: navigationBar.height*0.66
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    accentColor: applicationData.Theme.BackgroundColor
                    imageSource:
                    if(applicationData.IsDarkTheme === true)
                    {
                        return "../images/RightWhite.png";
                    }
                    else
                    {
                        return "../images/RightBlack.png";
                    }
                }
            }
        }
    }

}
