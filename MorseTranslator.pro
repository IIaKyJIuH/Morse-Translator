QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

VERSION="0.9.3"
QMAKE_TARGET_PRODUCT="MorseTranslator"
QMAKE_TARGET_COPYRIGHT="Pakulin Sergei Leonidovich"

DEFINES += \
	APP_VERSION='\\"$${VERSION}\\"' \
	APP_NAME='\\"$${QMAKE_TARGET_PRODUCT}\\"'

SOURCES += \
	configprog.cpp \
	dialog.cpp \
	main.cpp \
	mainwindow.cpp \
	translator.cpp

HEADERS += \
	configprog.h \
	dialog.h \
	mainwindow.h \
	translator.h

FORMS += \
	dialog.ui \
	mainwindow.ui

RESOURCES += resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
