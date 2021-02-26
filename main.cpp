#include "devicemanager.h"
#include "homeform.h"
#include "paletteform.h"
#include "colorpicker.h"
#include "fastonoff.h"
#include "settings.h"
#include "staticcolor.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);

//QCoreApplication Data
	QCoreApplication::setOrganizationName("Stephen-Hamilton-C");
	QCoreApplication::setApplicationName("SigmonLED");

//Qml Registrations:
	qmlRegisterType<DeviceManager>("StephenHamilton.SigmonLED.DeviceManager", 1, 0, "DeviceManager");
	qmlRegisterType<HomeForm>("StephenHamilton.SigmonLED.Home", 1, 0, "HomeBackend");
	qmlRegisterType<PaletteForm>("StephenHamilton.SigmonLED.Palette", 1, 0, "PaletteBackend");
	qmlRegisterType<ColorPicker>("StephenHamilton.SigmonLED.ColorPicker", 1, 0, "ColorPickerBackend");
	qmlRegisterType<FastOnOff>("StephenHamilton.SigmonLED.FastButtons", 1, 0, "FastBackend");
	qmlRegisterType<Settings>("StephenHamilton.SigmonLED.Settings", 1, 0, "SettingsBackend");
	qmlRegisterType<StaticColor>("StephenHamilton.SigmonLED.StaticColor", 1, 0, "StaticColorBackend");

	engine.load(url);

	return app.exec();
}
