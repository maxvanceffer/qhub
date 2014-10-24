# Add more folders to ship with the application, here
folder_01.source = qml/qhub_example
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    hubmanager.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qhub_src/release/ -lqhub
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qhub_src/debug/ -lqhub
else:unix: LIBS += -L$$OUT_PWD/../qhub_src/ -lqhub

INCLUDEPATH += $$PWD/../qhub_src
DEPENDPATH += $$PWD/../qhub_src

HEADERS += \
    hubmanager.h

RESOURCES += \
    qrc.qrc
