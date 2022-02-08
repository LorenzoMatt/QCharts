QT       += core gui
QT += charts
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    coordinataspezzata.cpp \
    creagraficobarrewidget.cpp \
    creatortaospezzatawidget.cpp \
    datigraficobarre.cpp \
    filereader.cpp \
    graficicontroller.cpp \
    graficobarre.cpp \
    graficobase.cpp \
    graficospezzata.cpp \
    graficotorta.cpp \
    main.cpp \
    mainwindow.cpp \
    utility.cpp

HEADERS += \
    coordinataspezzata.h \
    creagraficobarrewidget.h \
    creatortaospezzatawidget.h \
    datigraficobarre.h \
    filereader.h \
    graficicontroller.h \
    graficobarre.h \
    graficobase.h \
    graficospezzata.h \
    graficotorta.h \
    mainwindow.h \
    utility.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    css/style.css
