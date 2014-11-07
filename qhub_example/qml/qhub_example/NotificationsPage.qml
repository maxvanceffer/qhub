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

    ListView {
        id: notificationListView
        anchors.fill: parent
        anchors.margins: 10
        delegate: NotificationsDelegateItem{}
        model: NOTIFICATIONS.notifications
        spacing: 8
        move: Transition {
            NumberAnimation { properties: "x,y"; duration: 1000 }
        }

        onModelChanged: {
            console.log('Model changed to '+notificationListView.count);
        }
    }
}

