import QtQuick 2.0

Rectangle {
    width: 100
    height: 62

    Image {
        id: appBackground
        source: themeAppBackground
        fillMode: Image.Tile
        anchors.fill: parent
    }

    // The delegate for each section header
    Component {
        id: sectionHeading
        Rectangle {
            width: parent.width
            height: childrenRect.height
            color: "lightsteelblue"

            Text {
                text: section
                font.bold: true
            }
        }
    }

    ListView {
        id: notificationListView
        anchors.fill: parent
        anchors.margins: 10
        delegate: NotificationsDelegateItem{}
        model: NOTIFICATIONS.notifications
        section.property: "repositoryName"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeading
        spacing: 8
        move: Transition {
            NumberAnimation { properties: "x,y"; duration: 1000 }
        }

        onModelChanged: {
            console.log('Model changed to '+notificationListView.count);
        }
    }
}

