#include "devicemanager.h"

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
	qmlRegisterType<DeviceManager>("com.stephenhamilton.devicemanager", 1, 0, "DeviceManager");
	qmlRegisterType<HomeForm>("com.stephenhamilton.homeform", 1, 0, "HomeBackend");


	engine.load(url);

	return app.exec();
}
