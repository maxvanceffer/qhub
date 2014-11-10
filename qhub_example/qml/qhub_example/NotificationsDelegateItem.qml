import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {
    width: parent.width
    height: 62

    color: "transparent"

    Rectangle {
        id: readOrNot
        width: 2
        color: model.modelData.isRead ? "green" : "red";
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }

    Label {
        id: subjectText
        anchors.left: readOrNot.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        font.bold: true
        font.pixelSize: 16
        text: model.modelData.subject.title
        color: themeLabelColor
        elide: Text.ElideRight
    }

    Label {
        id: inRepoText
        anchors.left: readOrNot.right
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.leftMargin: 10
        font.bold: true
        font.pixelSize: 16
        text: "Repo: " + model.modelData.repository.name
        color: themeLabelColor
    }

    CheckBox {
        id: checkBox
        anchors.right: parent.right
        anchors.rightMargin: 2
        checked: model.modelData.isRead
        visible: !checked
        onCheckedChanged: {
            if(checked) {
                NOTIFICATIONS.markThreadAsRead(model.modelData);
            }
        }
    }
}

