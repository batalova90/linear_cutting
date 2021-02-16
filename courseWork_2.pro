QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11
QT += axcontainer
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    WorkWithAddedDetails.cpp \
    adapterdetails.cpp \
    barr.cpp \
    cut.cpp \
    detail.cpp \
    dialogaddbar.cpp \
    dialogadddetail.cpp \
    graphic.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    Profile.h \
    adapterdetails.h \
    barr.h \
    cut.h \
    detail.h \
    dialogaddbar.h \
    dialogadddetail.h \
    graphic.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    dialogaddbar.ui \
    dialogadddetail.ui \
    graphic.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    picture/picture.qrc
