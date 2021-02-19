#include "settings.h"
#include "configmanager.h"

#include <QJsonObject>

//Singleton
Settings* Settings::ptrInstance = nullptr;

Settings::Settings(QObject *parent) : QObject(parent)
{
	//Singleton
	if(ptrInstance != nullptr){
		delete this;
	}
	ptrInstance = this;

	//Plug into the ConfigManager to store settings
	connect(ConfigManager::getInstance(), &ConfigManager::read, this, &Settings::read);
	connect(ConfigManager::getInstance(), &ConfigManager::write, this, &Settings::write);

	qDebug() << "Settings Constructed";
}

void Settings::read(const QJsonObject &json)
{
	//Dark mode
	if(json.contains(jsonDarkMode) && json[jsonDarkMode].isBool()){
		darkMode = json[jsonDarkMode].toBool();
		emit darkModeChanged(darkMode);
	}

	//Auto Connect
	if(json.contains(jsonAutoConn) && json[jsonAutoConn].isBool()){
		autoConnect = json[jsonAutoConn].toBool();
		emit autoConnectChanged(autoConnect);
	}

	qDebug() << "Settings Read";
}

void Settings::write(QJsonObject &json)
{
	json[jsonDarkMode] = darkMode;
	json[jsonAutoConn] = autoConnect;

	qDebug() << "Settings Write";
}


