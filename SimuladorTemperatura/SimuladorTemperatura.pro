QT       += core gui

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CCell.cpp \
    CGrid.cpp \
    CMaterial.cpp \
    CMaterialCorrelacao.cpp \
    CMaterialInterpolacao.cpp \
    CRender3D.cpp \
    CReta.cpp \
    CSegmentoReta.cpp \
    CSimuladorTemperatura.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    CCell.h \
    CGrid.h \
    CMaterial.h \
    CMaterialCorrelacao.h \
    CMaterialInterpolacao.h \
    CRender3D.h \
    CReta.h \
    CSegmentoReta.h \
    CSimuladorTemperatura.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    gridButton.qrc
