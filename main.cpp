#include "devicemanager.h"
#include "homeform.h"
#include "paletteform.h"
#include "staticcolorform.h"
#include "fastonoff.h"

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


	//Qml Registrations
	qmlRegisterType<DeviceManager>("com.stephenhamilton.sigmonled.main", 1, 0, "DeviceManager");
	qmlRegisterType<HomeForm>("com.stephenhamilton.sigmonled.main", 1, 0, "HomeBackend");
	qmlRegisterType<PaletteForm>("com.stephenhamilton.sigmonled.main", 1, 0, "PaletteBackend");
	qmlRegisterType<StaticColorForm>("com.stephenhamilton.sigmonled.main", 1, 0, "StaticColorBackend");
	qmlRegisterType<FastOnOff>("com.stephenhamilton.sigmonled.main", 1, 0, "FastBackend");

	engine.load(url);

	return app.exec();
}
