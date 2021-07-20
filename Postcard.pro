QT       += core gui
QT  += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button.cpp \
    cave.cpp \
    chalk.cpp \
    couple.cpp \
    dancegame.cpp \
    deadman.cpp \
    dialogbox.cpp \
    digit.cpp \
    dog.cpp \
    dye.cpp \
    dyegame.cpp \
    game.cpp \
    kids.cpp \
    main.cpp \
    player.cpp \
    redwhite.cpp \
    riddle.cpp \
    riddlebox.cpp \
    snack.cpp \
    snackgame.cpp \
    speechline.cpp \
    tree.cpp \
    unicorn.cpp

HEADERS += \
    button.h \
    cave.h \
    chalk.h \
    couple.h \
    dancegame.h \
    deadman.h \
    dialogbox.h \
    digit.h \
    dog.h \
    dye.h \
    dyegame.h \
    game.h \
    kids.h \
    player.h \
    redwhite.h \
    riddle.h \
    riddlebox.h \
    snack.h \
    snackgame.h \
    speechline.h \
    tree.h \
    unicorn.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
