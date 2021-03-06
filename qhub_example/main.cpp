#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQml>
#include "qtquick2applicationviewer.h"

#include "../qhub_src/qhub.h"
#include "../qhub_src/hubnotificationmanager.h"

#include <iostream>       // std::cerr
#include <exception>      // std::set_terminate
#include <cstdlib>

void myterminate () {
  std::cerr << "terminate handler called\n";
  std::cerr << "Count objects " << HubNotification::debugObjectsCount();
  std::cerr << HubNotification::debugObjectsCount();
  abort();  // forces abnormal termination
}

int main(int argc, char *argv[])
{
    std::set_terminate (myterminate);
    QGuiApplication app(argc, argv);

    qmlRegisterType<HubAuthority>("my.HubAuthority", 1, 0, "HubAuthority");
    qmlRegisterType<HubSubject>("my.HubSubject", 1, 0, "HubSubject");
    qmlRegisterType<HubRepository>("my.HubRepository", 1, 0, "HubRepository");
    qmlRegisterType<HubNotification>("my.HubNotification", 1, 0, "HubNotification");
    qmlRegisterType<HubUser>("my.hubuser", 1, 0, "HubUser");

    app.setApplicationDisplayName("GitHub Friend");
    app.setApplicationName("GitHub Friend");

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("HUB",QHub::instance());
    viewer.rootContext()->setContextProperty("NOTIFICATIONS",HubNotificationManager::instance());
    viewer.setMainQmlFile(QStringLiteral("qml/qhub_example/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
