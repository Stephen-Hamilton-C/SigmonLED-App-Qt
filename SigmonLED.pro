QT += quick bluetooth

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        devicemanager.cpp \
        fastonoff.cpp \
        homeform.cpp \
        main.cpp \
        paletteform.cpp \
        staticcolorform.cpp

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
	devicemanager.h \
	fastonoff.h \
	homeform.h \
	paletteform.h \
	staticcolorform.h

DISTFILES += \
	android/AndroidManifest.xml \
	android/build.gradle \
	android/gradle.properties \
	android/gradle/wrapper/gradle-wrapper.jar \
	android/gradle/wrapper/gradle-wrapper.properties \
	android/gradle/wrapper/gradle-wrapper.properties.new \
	android/gradlew \
	android/gradlew.bat \
	android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
