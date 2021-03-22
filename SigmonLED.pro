QT += quick bluetooth

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        colorpicker.cpp \
        colorrgb.cpp \
        devicemanager.cpp \
        fastonoff.cpp \
        homeform.cpp \
        main.cpp \
        palette.cpp \
        palettecolormodel.cpp \
        paletteform.cpp \
        settings.cpp \
        staticcolor.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
	colorpicker.h \
	colorrgb.h \
	devicemanager.h \
	fastonoff.h \
	homeform.h \
	palette.h \
	palettecolormodel.h \
	paletteform.h \
	settings.h \
	staticcolor.h

RC_ICONS = icons/SigmonLED_Icon.ico

DISTFILES += \
	Changelog.md \
	android/AndroidManifest.xml \
	android/build.gradle
	README.md

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
