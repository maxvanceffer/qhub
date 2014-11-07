import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts  1.1

Rectangle {
    id: root
    width: 100
    height: 62

    clip: true

    property string textColor: 'white'
    property alias awasomeIcon: awasomeLabel.text
    property alias awasomeIconColor: awasomeLabel.color
    property alias pngIcon: pngIcon.source
    property alias iconText: iconText.text
    property alias footerColor: gridItemFooter.color
    property alias footerText: footerText.text
    property string footerBorderColor: 'white'

    // Size changes animation
    property int normalWidth: 100
    property int normalHeight: 100
    property int smallSize: 10

    signal clicked();

    Behavior on width { SmoothedAnimation { velocity: 200 } }
    Behavior on height { SmoothedAnimation { velocity: 200 } }

    states: [
        State {
            name: "small"
            PropertyChanges { target: root; height: smallSize; width: smallSize }
        },
        State {
            name: "normal"
            when: !mouseArea.containsMouse
            PropertyChanges { target: root; height: normalHeight; width: normalWidth }
        },
        State {
            name: "hover"
            when: mouseArea.containsMouse
            PropertyChanges { target: root; height: normalHeight + 20; width: normalWidth + 20 }
        }

    ]

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked()
    }

    RowLayout {
        id: textAndIconLayout
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: gridItemFooter.top
        anchors.margins: 8
        anchors.bottomMargin: -2
        spacing: 6

        Label {
            id: awasomeLabel
            visible: awasomeIcon.length
            text: awasomeIcon
            font.pixelSize: Math.round(parent.height / 2.5);
            font.family: "FontAwesome"
            color: textColor
        }

        Image {
            id: pngIcon
            visible: !awasomeLabel.visible
        }

        Label {
            id: iconText
            color: textColor
            font.pixelSize: Math.round(parent.height / 5);
            font.bold: true
            renderType: Text.NativeRendering
        }
    }

    Rectangle {
        id: gridItemFooter
        border.width: 1
        border.color: footerBorderColor
        height: 25

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottomMargin: -1
        anchors.leftMargin: -1
        anchors.rightMargin: -1

        Label {
            id: footerText
            anchors.fill: parent
            anchors.margins: 4
            color: textColor
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
