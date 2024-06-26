QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    conveyor.cpp \
    cutter.cpp \
    cutter_m.cpp \
    gamescene.cpp \
    global.cpp \
    hub.cpp \
    machine.cpp \
    main.cpp \
    merger.cpp \
    mine.cpp \
    mine_place.cpp \
    miner.cpp \
    pausemenu.cpp \
    rotater.cpp \
    shopmenu.cpp \
    square.cpp \
    sub_hub.cpp \
    trashcan.cpp \
    window.cpp

HEADERS += \
    conveyor.h \
    cutter.h \
    cutter_m.h \
    gamescene.h \
    global.h \
    hub.h \
    machine.h \
    merger.h \
    mine.h \
    mine_place.h \
    miner.h \
    pausemenu.h \
    rotater.h \
    shopmenu.h \
    square.h \
    sub_hub.h \
    trashcan.h \
    window.h

FORMS += \
    gamescene.ui \
    pausemenu.ui \
    shopmenu.ui \
    window.ui

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
