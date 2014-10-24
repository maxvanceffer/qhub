import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Rectangle {
    width: 100
    height: 62

    property alias rootIcon: currentDashboardIcon;
    property alias rootText: currentStateText;
    property alias publicReposNumber: reposNumbers.text
    property alias publicGistsNumber: gistsNumbers.text

    function setProfileImg( url )
    {
        currentDashboardIcon.source = url
    }

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

    Label {
        id: currentStateText
        opacity: 0
        anchors {
            left: currentDashboardIcon.right
            leftMargin: 8
            top: parent.top
            topMargin: 18
        }

        font.bold: true
        font.pixelSize: 14

        states: [
            State {
                name: "init"
                AnchorChanges { target: currentStateText; anchors.left: parent.right; }
                PropertyChanges { target: currentStateText; opacity: 0 }
            },
            State {
                name: "visible";
                AnchorChanges { target: currentStateText; anchors.left: currentDashboardIcon.right; }
                PropertyChanges { target: currentStateText; opacity: 1 }
            }
        ]

        transitions: Transition {
            AnchorAnimation { easing.type: Easing.InOutCirc; duration: 1200; easing.amplitude: 4.0 }
            SmoothedAnimation { duration: 500; }
        }
    }

    RowLayout {
        id: reposLayout
        anchors.top: currentStateText.bottom
        anchors.left: currentStateText.left
        anchors.topMargin: 4
        spacing: 4
        opacity: currentStateText.opacity

        Label {
            id: reposIcon
            text: '\uf126'
            font.pixelSize: 20
            font.family: "FontAwesome"
        }

        Label {
            id: reposNumbers
            text: '0'
            font.pixelSize: 20
        }

        Label {
            id: gistsIcon
            text: '\uf1c9'
            font.pixelSize: 15
            font.family: "FontAwesome"
        }

        Label {
            id: gistsNumbers
            text: '0'
            font.pixelSize: 20
        }
    }
}
