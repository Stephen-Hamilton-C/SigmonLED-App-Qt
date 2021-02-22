#include "settings.h"

#include <QTimer>

Settings::Settings(QObject *parent) : QObject(parent)
{
	QTimer::singleShot(100, this, &Settings::emitInit);
}

void Settings::emitInit()
{
	emit autoConnectChanged(autoConnect());
	emit darkModeChanged(darkMode());
}

bool Settings::darkMode()
{
	return settings.value("DarkMode", false).toBool();
}

void Settings::setDarkMode(bool darkMode)
{
	settings.setValue("DarkMode", darkMode);
}

bool Settings::autoConnect()
{
	return settings.value("AutoConnect", false).toBool();
}

void Settings::setAutoConnect(bool autoConnect)
{
	settings.setValue("AutoConnect", autoConnect);
}
