QT += quick bluetooth

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        colorpicker.cpp \
        colorrgb.cpp \
        custompalettesform.cpp \
        devicemanager.cpp \
        fastonoff.cpp \
        homeform.cpp \
        main.cpp \
        palette.cpp \
        paletteeditorform.cpp \
        paletteeditorlist.cpp \
        paletteeditormodel.cpp \
        paletteform.cpp \
        palettelist.cpp \
        palettemodel.cpp \
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
	custompalettesform.h \
	devicemanager.h \
	fastonoff.h \
	homeform.h \
	palette.h \
	paletteeditorform.h \
	paletteeditorlist.h \
	paletteeditormodel.h \
	paletteform.h \
	palettelist.h \
	palettemodel.h \
	settings.h \
	staticcolor.h

RC_ICONS = icons/SigmonLED_Icon.ico

DISTFILES += \
	CHANGELOG.md \
	README.md \
	RELEASE-CHECKLIST.md \
	TODO.md \
	android/AndroidManifest.xml \
	android/build.gradle \
	android/gradle.properties \
	android/gradle/wrapper/gradle-wrapper.jar \
	android/gradle/wrapper/gradle-wrapper.properties \
	android/gradlew \
	android/gradlew.bat \
	android/res/values/libs.xml

#ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

contains(ANDROID_TARGET_ARCH,x86_64) {
	ANDROID_PACKAGE_SOURCE_DIR = \
		$$PWD/android
}

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
	ANDROID_PACKAGE_SOURCE_DIR = \
		$$PWD/android
}

TARGET = SigmonLED
ANDROID_VERSION_CODE = "1"
ANDROID_VERSION_NAME = "0.5.0-beta"
