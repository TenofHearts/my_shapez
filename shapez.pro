QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/conveyor.cpp \
    src/cutter.cpp \
    src/cutter_m.cpp \
    src/gamescene.cpp \
    src/global.cpp \
    src/hub.cpp \
    src/machine.cpp \
    src/main.cpp \
    src/merger.cpp \
    src/mine.cpp \
    src/mine_place.cpp \
    src/miner.cpp \
    src/pausemenu.cpp \
    src/rotater.cpp \
    src/shopmenu.cpp \
    src/square.cpp \
    src/sub_hub.cpp \
    src/trashcan.cpp \
    src/window.cpp

HEADERS += \
    header/conveyor.h \
    header/cutter.h \
    header/cutter_m.h \
    header/gamescene.h \
    header/global.h \
    header/hub.h \
    header/machine.h \
    header/merger.h \
    header/mine.h \
    header/mine_place.h \
    header/miner.h \
    header/pausemenu.h \
    header/rotater.h \
    header/shopmenu.h \
    header/square.h \
    header/sub_hub.h \
    header/trashcan.h \
    header/window.h

FORMS += \
    ui/gamescene.ui \
    ui/pausemenu.ui \
    ui/shopmenu.ui \
    ui/window.ui

RC_FILE += icon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    .gitignore \
    README.md
