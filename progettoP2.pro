QT += core gui
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
    datigraficobarre.cpp \
    filereader.cpp \
    graficicontroller.cpp \
    graficobarre.cpp \
    graficobarrewidget.cpp \
    graficobase.cpp \
    graficobasewidget.cpp \
    graficononsalvato.cpp \
    graficospezzata.cpp \
    graficospezzatawidget.cpp \
    graficotorta.cpp \
    graficotortawidget.cpp \
    gridlayuotutil.cpp \
    inseriscititolowidget.cpp \
    main.cpp \
    mainwindow.cpp \
    tortaospezzatawidget.cpp \
    utility.cpp

HEADERS += \
    coordinataspezzata.h \
    creagraficobarrewidget.h \
    datigraficobarre.h \
    filereader.h \
    graficicontroller.h \
    graficobarre.h \
    graficobarrewidget.h \
    graficobase.h \
    graficobasewidget.h \
    graficononsalvato.h \
    graficospezzata.h \
    graficospezzatawidget.h \
    graficotorta.h \
    graficotortawidget.h \
    gridlayuotutil.h \
    inseriscititolowidget.h \
    mainwindow.h \
    tortaospezzatawidget.h \
    utility.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
