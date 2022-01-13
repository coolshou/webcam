QT     += core gui network webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 0.0.1.0
QMAKE_TARGET_COMPANY="coolshou.idv.tw"
QMAKE_TARGET_DESCRIPTION="webcam for old ipcam"
QMAKE_TARGET_COPYRIGHT="coolshou©2021"
QMAKE_TARGET_PRODUCT="webcam"

CONFIG += c++11
unix {
    QMAKE_LFLAGS += -no-pie
}
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/mainwindow.h

FORMS += \
    src/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/webcam.qrc

DISTFILES += \
    webcam.ini

unix {
    desktop.files  = webcam.desktop
    desktop.path   = /usr/share/applications/
    INSTALLS       += desktop
    images.files = src/images/webcam.png
    images.path   = /usr/share/pixmaps/
    INSTALLS       += images
}

win32 {
    RC_ICONS = src/images/webcam.ico
    DEPLOY_COMMAND += $$shell_quote($$shell_path($$[QT_INSTALL_BINS]\windeployqt))
    DEPLOY_TARGET_EXE = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}.exe))
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}-$${VERSION}))
    QMAKE_POST_LINK = $$quote(cmd /c if not exist "$${DEPLOY_TARGET}" mkdir "$${DEPLOY_TARGET}"$$escape_expand(\\n\\t))
    QMAKE_POST_LINK += $$quote(cmd /c copy /y $${DEPLOY_TARGET_EXE} "$${DEPLOY_TARGET}\\" $$escape_expand(\\n\\t))
    QMAKE_POST_LINK += $$quote(cmd /c $${DEPLOY_COMMAND} $${DEPLOY_TARGET}\\$${TARGET}.exe $$escape_expand(\\n\\t))
    
}
