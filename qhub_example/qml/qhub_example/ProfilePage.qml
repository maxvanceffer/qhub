import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Rectangle {

    property var profile: null;

    Image {
        id: currentDashboardIcon
        width: 50; height: 50
        smooth: true
        anchors {
            left: parent.left
            leftMargin: 10
            bottom: parent.top
        }

        states: [
            State {
                name: "init"
                AnchorChanges { target: currentDashboardIcon; anchors.bottom: parent.top; anchors.top: undefined }
            },
            State {
                name: "visible";
                AnchorChanges { target: currentDashboardIcon; anchors.bottom: undefined; anchors.top: parent.top }
            }
        ]

        transitions: Transition {
            AnchorAnimation { easing.type: Easing.InOutCirc; duration: 500; easing.amplitude: 4.0 }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: routerView.replace(profilePage);
        }
    }

    ColumnLayout {
        id: profileLayout

        anchors.left: currentDashboardIcon.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: currentDashboardIcon.bottom
        anchors.margins: 8

        RowLayout {
            id: nameLayout

            Label {
                id: nameLabel
                text: qsTr("Name:")
                font.bold: true
            }

            Label {
                id: nameValue
                text: profile ? profile.name : ''
            }
        }

        RowLayout {
            Label {
                id: loginLabel
                text: qsTr("Login:")
                font.bold: true
            }

            Label {
                id: loginValue
                text: profile ? profile.login : ''
            }
        }

        RowLayout {
            Label {
                id: locationLabel
                text: qsTr("Location:")
                font.bold: true
            }

            Label {
                id: locationValue
                text: profile ? profile.location : ''
            }
        }

        RowLayout {
            Label {
                id: companyLabel
                text: qsTr("Company:")
                font.bold: true
            }

            Label {
                id: companyValue
                text: profile ? profile.company : ''
            }
        }

        RowLayout {
            Label {
                id: blogLabel
                text: qsTr("Blog:")
                font.bold: true
            }

            Label {
                id: blogValue
                text: profile ? profile.blog : ''
            }
        }

        RowLayout {
            Label {
                id: emailLabel
                text: qsTr("Email:")
                font.bold: true
            }

            Label {
                id: emailValue
                text: profile ? profile.email : ''
            }
        }

        RowLayout {
            Label {
                id: bioLabel
                text: qsTr("Bio:")
                font.bold: true
            }

            Label {
                id: bioValue
                text: profile ? profile.bio : ''
            }
        }
    }

    Connections {
        target: HUB
        onUserProfileUpdated: {
            currentDashboardIcon.source = HUB.authority.profile.avatar;
            currentDashboardIcon.state  = "visible"
            profile = HUB.authority.profile;
        }
    }
}
