import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import Qt.labs.qmlmodels

Item
{
    id: root

    property variant userModel: []

    signal editRequested(int mode);

    Component.onCompleted:
    {
        userModel = applicationData.UserList
    }

    Rectangle
    {
        color: applicationData.Theme.BackgroundColor
        anchors.fill: parent
    }

    Rectangle
    {
        id: tableHeader
        height: applicationData.Theme.BarHeight*0.75
        width: parent.width
        color: applicationData.Theme.ControlColor

        Rectangle
        {
            border.color: "darkgrey"
            height: 1
            width: parent.width
            anchors.top: tableHeader.top
        }

        Rectangle
        {
            border.color: "darkgrey"
            height: 1
            width: parent.width
            anchors.bottom: tableHeader.bottom
        }

        CheckBox
        {
            id: mark
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 10
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
        }

        Label
        {
            id: userid
            text: "User Id"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: mark.right
            width: parent.width*0.15
            color: applicationData.Theme.FontColor
        }

        Label
        {
            id: firstname
            text: "Firstname"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: userid.right
            width: parent.width*0.18
            color: applicationData.Theme.FontColor
        }

        Label
        {
            id: lastname
            text: "Lastname"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: firstname.right
            width: parent.width*0.17
            color: applicationData.Theme.FontColor
        }

        Label
        {
            id: emailid
            text: "Email Id"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: lastname.right
            width: parent.width*0.25
            color: applicationData.Theme.FontColor
        }

        Label
        {
            id: contactno
            text: "Contact No."
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: emailid.right
            width: parent.width*0.20
            color: applicationData.Theme.FontColor
        }
    }

    ListView
    {
        id: userListView
        height: parent.height - tableHeader.height
        width: parent.width
        anchors.top: tableHeader.bottom
        visible: true
        spacing: 0
        clip: true
        model: userModel
        delegate: userListDelegate
    }

    Component
    {
        id: userListDelegate

        Rectangle
        {
            id: userItem
            width: userListView.width
            height: tableHeader.height
            radius: 0
            color: applicationData.Theme.ControlLowColor

            CheckBox
            {
                id: markItem
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
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
            }

            Label
            {
                id: useridItem
                text: applicationData.UserList[index].UserId
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: markItem.right
                width: parent.width*0.15
                color: applicationData.Theme.FontColor
            }

            Label
            {
                id: firstnameItem
                text: applicationData.UserList[index].FirstName
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: useridItem.right
                width: parent.width*0.18
                color: applicationData.Theme.FontColor
            }

            Label
            {
                id: lastnameItem
                text: applicationData.UserList[index].LastName
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: firstnameItem.right
                width: parent.width*0.17
                color: applicationData.Theme.FontColor
            }

            Label
            {
                id: emailidItem
                text: applicationData.UserList[index].EmailId
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: lastnameItem.right
                width: parent.width*0.25
                color: applicationData.Theme.FontColor
            }

            Label
            {
                id: contactnoItem
                text: applicationData.UserList[index].ContactNo
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: emailidItem.right
                width: parent.width*0.20
                color: applicationData.Theme.FontColor
            }

            ToolButton
            {
                id: editBtnItem
                height: tableHeader.height*0.75
                width: tableHeader.height*0.75
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 5
                anchors.right: deleteBtnItem.left

                icon.source:
                {

                    if(applicationData.IsDarkTheme === true)
                    {
                        return "../images/EditWhite.png"
                    }
                    else
                    {
                        return "../images/EditBlack.png"
                    }
                }

                icon.color: "transparent"
                icon.height: tableHeader.height*0.75
                icon.width: tableHeader.height*0.75

                background: Rectangle
                {
                    color: applicationData.Theme.ControlLowColor
                }

                onClicked:
                {
                    editUser(index);
                }
            }

            ToolButton
            {
                id: deleteBtnItem
                height: tableHeader.height*0.75
                width: tableHeader.height*0.75
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 10
                anchors.right: parent.right

                icon.source:
                {

                    if(applicationData.IsDarkTheme === true)
                    {
                        return "../images/DeleteWhite.png"
                    }
                    else
                    {
                        return "../images/DeleteBlack.png"
                    }
                }

                icon.color: "transparent"
                icon.height: tableHeader.height*0.75
                icon.width: tableHeader.height*0.75

                background: Rectangle
                {
                    color: applicationData.Theme.ControlLowColor
                }
            }
        }
    }

    function deleteUser(index)
    {
    }

    function editUser(index)
    {
        editRequested(index);
    }

    Connections
    {
        target: applicationData

        function onUserAction()
        {
            userModel = applicationData.UserList
        }
    }
}
