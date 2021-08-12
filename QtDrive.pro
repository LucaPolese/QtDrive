QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Control/controller.cpp \
    Model/account.cpp \
    main.cpp \
    Model/deepptr.cpp \
    Model/file.cpp \
    Model/filearchivio.cpp \
    Model/fileaudio.cpp \
    Model/fileimmagine.cpp \
    Model/filemedia.cpp \
    Model/filetesto.cpp \
    Model/filevideo.cpp \
    Model/mainwindow.cpp

HEADERS += \
    Control/controller.h \
    Model/account.h \
    Model/deepptr.h \
    Model/file.h \
    Model/filearchivio.h \
    Model/fileaudio.h \
    Model/fileimmagine.h \
    Model/filemedia.h \
    Model/filetesto.h \
    Model/filevideo.h \
    Model/mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = res/icons/icon.ico
