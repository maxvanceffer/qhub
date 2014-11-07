import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {
    width: 300
    height: 450
    focus: true

    property string themeAppLogo: 'images/github.png'
    property string themeAppBackground: 'images/footer_lodyas.png'
    property string themeLabelColor: '#fff'

    // HUB data
    property var hubProfile: undefined;

    Keys.onReleased: {
        if( event.key === Qt.Key_Backspace ) {
            // 2 - Becouse 1 is login page
            if (routerView.depth > 2) {
                routerView.pop();
                event.accepted = true;
            }
        }
    }

    FontLoader {
        id: awasomeFont
        source: "fonts/fontawesome-webfont.ttf"
    }

    LoginPage {
        id: loginPage
    }

    DashboardPage {
        id: dashboardPage
        onShowNotification: {
             routerView.push(notificationsPage);
        }
    }

    ProfilePage {
        id: profilePage
    }

    NotificationsPage {
        id: notificationsPage
    }

    StackView {
        id: routerView
        anchors.fill: parent
        initialItem: loginPage
    }

    Connections {
        target: HUB
        onUserAuthorized: {
            routerView.push(dashboardPage);
        }
        onUserProfileUpdated: {
            hubProfile = HUB.authority.profile;

            dashboardPage.setProfileImg(HUB.authority.profile.avatar);
            dashboardPage.rootText.text     =  HUB.authority.profile.login + "( " + HUB.authority.profile.name + " )";
            dashboardPage.publicReposNumber = HUB.authority.profile.publicRepos;
            dashboardPage.publicGistsNumber = HUB.authority.profile.publicGists;
        }
    }
}
