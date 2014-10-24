import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {
    width: 360
    height: 360

    FontLoader {
        id: awasomeFont
        source: "fonts/fontawesome-webfont.ttf"
    }

    LoginPage {
        id: loginPage
    }

    DashboardPage {
        id: dashboardPage
    }

    ProfilePage {
        id: profilePage
    }

    StackView {
        id: routerView
        anchors.fill: parent
        initialItem: loginPage
    }

    Connections {
        target: HUB
        onUserAuthorized: {
            routerView.replace(dashboardPage);
        }
        onUserProfileUpdated: {
            dashboardPage.setProfileImg(HUB.authority.profile.avatar);
            dashboardPage.rootText.text  =  HUB.authority.profile.login + "( " + HUB.authority.profile.name + " )";
            dashboardPage.publicReposNumber = HUB.authority.profile.publicRepos;
            dashboardPage.publicGistsNumber = HUB.authority.profile.publicGists;
            dashboardPage.rootIcon.state = "visible";
            dashboardPage.rootText.state = "visible";
        }
    }
}
