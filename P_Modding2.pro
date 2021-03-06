QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    ParView.cpp \
    allpar.cpp \
    codeeditor.cpp \
    createcopynewfiledialog.cpp \
    custominterfacedialog.cpp \
    findtextdialog.cpp \
    gamefiles.cpp \
    highlighter.cpp \
    main.cpp \
    maineditor.cpp \
    mainwindow.cpp \
    modifOpener.cpp \
    modifViewOld.cpp \
    modmodel.cpp \
    newfilebutton.cpp \
    onlyfilesystemmodel.cpp \
    parareader.cpp \
    parviewsortfilterproxymodel.cpp \
    primparseryaml.cpp \
    tabeditor.cpp \
    toolbar.cpp \
    workWindow.cpp \
    writeplacedialog.cpp

HEADERS += \
    allpar.h \
    codeeditor.h \
    createcopynewfiledialog.h \
    custominterfacedialog.h \
    findtextdialog.h \
    gamefiles.h \
    highlighter.h \
    maineditor.h \
    mainwindow.h \
    modifOpener.h \
    modifViewOld.h \
    modmodel.h \
    newfilebutton.h \
    onlyfilesystemmodel.h \
    parareader.h \
    parview.h \
    parviewsortfilterproxymodel.h \
    primparseryaml.h \
    tabeditor.h \
    toolbar.h \
    workWindow.h \
    writeplacedialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES +=
