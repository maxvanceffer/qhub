import QtQuick 2.0
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0

Rectangle {
    width: 100
    height: 62

    property alias username: usernameInput.text
    property alias password: passwordInput.text

    Keys.onPressed: {
        if(event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
            loginHub();
            event.accepted = true;
        }
    }

    Image {
        id: appBackground
        source: themeAppBackground
        fillMode: Image.Tile
        anchors.fill: parent
    }

    Rectangle {
        id: loginErrorMsgRec
        color: "lightcyan"
        visible: errorMsg.visible
        border.color: "cyan"
        border.width: 1

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 10
        }

        Label {
            id: errorMsg
            text: HUB.error
            visible: HUB.error.length
            color: "red"
            font.bold: true
            font.italic: true
        }
    }

    Image {
        id: githubLogo
        source: themeAppLogo
        fillMode: Image.PreserveAspectFit
        smooth: true
        anchors.bottom: credLayout.top
        anchors.margins: 10
        anchors.horizontalCenter: credLayout.horizontalCenter
        width: credLayout.width / 1.1
        height: width
    }

    DropShadow {
        anchors.fill: githubLogo
        horizontalOffset: 0
        verticalOffset: 0
        radius: 3.0
        samples: 8
        color: "#E0D8E0"
        source: githubLogo
    }

    Column {
        id: credLayout
        anchors.centerIn: parent
        spacing: 8
        TextField {
            id: usernameInput
            text: "maxvanceffer"
            placeholderText: qsTr("Useraname")
        }

        TextField {
            id: passwordInput
            echoMode: TextInput.Password
            text: "arofas46"
            placeholderText: qsTr("Password")
        }

        Button {
            id: loginBtn
            text: qsTr("Login")
            onClicked: loginHub()
            width: passwordInput.width
            enabled: usernameInput.text.length && passwordInput.text.length
        }
    }

    function loginHub() {
        if(!loginBtn.enabled) return;

        HUB.login(usernameInput.text,passwordInput.text)
    }
}
