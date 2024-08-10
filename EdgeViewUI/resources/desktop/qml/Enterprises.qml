import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

Item
{
    id: root

    property variant enterpriseModel: []

    signal editRequested(int mode);

    Component.onCompleted:
    {
        enterpriseModel = applicationData.EnterpriseList
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
            id: enterpriseid
            text: "Enterprise Id"
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
            anchors.left: enterpriseid.right
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
            text: "Phone No."
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: emailid.right
            width: parent.width*0.20
            color: applicationData.Theme.FontColor
        }
    }

    ListView
    {
        id: enterpriseListView
        height: parent.height - tableHeader.height
        width: parent.width
        anchors.top: tableHeader.bottom
        visible: true
        spacing: 0
        clip: true
        model: enterpriseModel
        delegate: enterpriseListDelegate
    }

    Component
    {
        id: enterpriseListDelegate

        Rectangle
        {
            id: enterpriseItem
            width: enterpriseListView.width
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
                id: enterpriseidItem
                text: applicationData.EnterpriseList[index].EnterpriseId
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: markItem.right
                width: parent.width*0.15
                color: applicationData.Theme.FontColor
            }

            Label
            {
                id: firstnameItem
                text: applicationData.EnterpriseList[index].ContactFirstName
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: enterpriseidItem.right
                width: parent.width*0.18
                color: applicationData.Theme.FontColor
            }

            Label
            {
                id: lastnameItem
                text: applicationData.EnterpriseList[index].ContactLastName
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: firstnameItem.right
                width: parent.width*0.17
                color: applicationData.Theme.FontColor
            }

            Label
            {
                id: emailidItem
                text: applicationData.EnterpriseList[index].ContactEmailId
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: lastnameItem.right
                width: parent.width*0.25
                color: applicationData.Theme.FontColor
            }

            Label
            {
                id: phonenoItem
                text: applicationData.EnterpriseList[index].ContactPhoneNo
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

    function deleteEnterprise(index)
    {
    }

    function editEnterprise(index)
    {
        editRequested(index);
    }

    Connections
    {
        target: applicationData

        function onEnterpriseAction()
        {
            enterpriseModel = applicationData.EnterpriseList
        }
    }
}
