import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Rectangle {
    id: root
    width: 100
    height: 62

    property alias rootIcon: currentDashboardIcon;
    property alias rootText: currentStateText;
    property alias publicReposNumber: reposNumbers.text
    property alias publicGistsNumber: gistsNumbers.text
    property string currentState: "init"

    function setProfileImg( url )
    {
        currentDashboardIcon.source = url
    }

    Connections {
        target: routerView
        onCurrentItemChanged: {
            dashboardPage.currentState = (routerView.currentItem == dashboardPage) ? "visible" : "init";
        }
    }

    Image {
        id: appBackground
        source: themeAppBackground
        fillMode: Image.Tile
        anchors.fill: parent
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

        state: currentState;

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
            ParallelAnimation {
                AnchorAnimation { easing.type: Easing.InOutCirc; duration: 500; easing.amplitude: 2.0 }
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                routerView.push(profilePage);
            }
        }
    }

    Label {
        id: currentStateText
        opacity: 0
        color: themeLabelColor
        anchors {
            left: currentDashboardIcon.right
            top: parent.top
            leftMargin: 8
            topMargin: 8
        }

        font.bold: true
        font.pixelSize: 14
        state: currentState;
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
            ParallelAnimation {
                AnchorAnimation { easing.type: Easing.InOutCirc; duration: 500; easing.amplitude: 2.0 }
                SmoothedAnimation { duration: 500; }
            }
        }
    }

    RowLayout {
        id: reposLayout
        anchors.top: currentStateText.bottom
        anchors.left: currentStateText.left
        anchors.leftMargin: 4
        spacing: 4
        opacity: currentStateText.opacity

        Label {
            id: reposIcon
            text: '\uf126'
            font.pixelSize: 20
            font.family: "FontAwesome"
            color: themeLabelColor
        }

        Label {
            id: reposNumbers
            text: '0'
            font.pixelSize: 20
            color: themeLabelColor
        }

        Label {
            id: gistsIcon
            text: '\uf1c9'
            font.pixelSize: 15
            font.family: "FontAwesome"
            color: themeLabelColor
        }

        Label {
            id: gistsNumbers
            text: '0'
            font.pixelSize: 20
            color: themeLabelColor
        }
    }

    GridLayout {
        id: dashboardGridLayout

        anchors.top: reposLayout.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10

        columns: 2
        columnSpacing: 12
        rows: 2
        rowSpacing: 12

        DashboardGridItem {
            id: reposFlatIcon
            color: '#2ecc71'
            footerColor: '#27ae60'
            footerBorderColor: '#209250'
            footerText: qsTr('Repositories')
            iconText: hubProfile ? hubProfile.publicRepos : 0
            awasomeIcon: '\uf126'
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        DashboardGridItem {
            id: gistsFlatIcon
            color: '#9b59b6'
            footerColor: '#8e44ad'
            footerBorderColor: '#703688'
            footerText: qsTr('Gists')
            iconText: hubProfile ? hubProfile.publicGists : 0
            awasomeIcon: '\uf1c9'
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        DashboardGridItem {
            id: issuesFlatIcon
            color: '#2ecc71'
            footerColor: '#27ae60'
            footerBorderColor: '#209250'
            footerText: qsTr('Issues')
            awasomeIcon: '\uf126'
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        DashboardGridItem {
            id: eventsFlatIcon
            color: '#2ecc71'
            footerColor: '#27ae60'
            footerBorderColor: '#209250'
            footerText: qsTr('Events')
            awasomeIcon: '\uf126'
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
