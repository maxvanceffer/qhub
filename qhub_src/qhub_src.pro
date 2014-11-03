#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T15:03:36
#
#-------------------------------------------------

QT       += network gui
TARGET    = qhub
TEMPLATE  = lib
DEFINES  += QHUB_LIBRARY
VERSION   = 0.1
DISTDIR   = lib

!macx: CONFIG += static_and_shared

SOURCES += qhub.cpp \
    networkconnection.cpp \
    networkmanager.cpp \
    jsonparser.cpp \
    appinfo.cpp \
    hubauthority.cpp \
    hubuser.cpp \
    hubrepo.cpp \
    hubissues.cpp \
    hubnotificationmanager.cpp \
    hubnotification.cpp

HEADERS += qhub.h\
    qhub_global.h \
    networkconnection.h \
    networkmanager.h \
    jsonparser.h \
    appinfo.h \
    hubauthority.h \
    hubuser.h \
    hubrepo.h \
    hubissues.h \
    hubnotificationmanager.h \
    hubnotification.h

unix {
copyCommand =
for(deploymentfolder, DEPLOYMENTFOLDERS) {
    source = $$MAINPROFILEPWD/$$eval($${deploymentfolder}.source)
    source = $$replace(source, \\\\, /)
    macx {
        target = $$OUT_PWD/$${TARGET}.app/Contents/Resources/$$eval($${deploymentfolder}.target)
    } else {
        target = $$OUT_PWD/$$eval($${deploymentfolder}.target)
    }
    target = $$replace(target, \\\\, /)
    sourcePathSegments = $$split(source, /)
    targetFullPath = $$target/$$last(sourcePathSegments)
    targetFullPath ~= s,/\\.?/,/,
    !isEqual(source,$$targetFullPath) {
        !isEmpty(copyCommand):copyCommand += &&
        copyCommand += $(MKDIR) \"$$target\"
        copyCommand += && $(COPY_DIR) \"$$source\" \"$$target\"
    }
}
!isEmpty(copyCommand) {
    copyCommand = @echo Copying application data... && $$copyCommand
    copydeploymentfolders.commands = $$copyCommand
    first.depends = $(first) copydeploymentfolders
    export(first.depends)
    export(copydeploymentfolders.commands)
    QMAKE_EXTRA_TARGETS += first copydeploymentfolders
}
}
!isEmpty(target.path) {
installPrefix = $${target.path}
} else {
installPrefix = /usr/lib/$${TARGET}
}
for(deploymentfolder, DEPLOYMENTFOLDERS) {
item = item$${deploymentfolder}
itemfiles = $${item}.files
$$itemfiles = $$eval($${deploymentfolder}.source)
itempath = $${item}.path
$$itempath = $${installPrefix}/$$eval($${deploymentfolder}.target)
export($$itemfiles)
export($$itempath)
INSTALLS += $$item
}

!isEmpty(desktopfile.path) {
export(icon.files)
export(icon.path)
export(desktopfile.files)
export(desktopfile.path)
INSTALLS += icon desktopfile
}

isEmpty(target.path) {
target.path = $${installPrefix}/bin
export(target.path)
}

INSTALLS += target
INCLUDEPATH += /home/
#LIBS += -lssl -lcrypto
