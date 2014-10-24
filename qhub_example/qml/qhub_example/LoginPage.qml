import QtQuick 2.0
import QtQuick.Controls 1.1

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
