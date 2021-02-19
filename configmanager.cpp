#include "configmanager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>

//Singleton
ConfigManager* ConfigManager::ptrInstance = nullptr;

ConfigManager::ConfigManager(QObject *parent) : QObject(parent)
{
	//Singleton
	if(ptrInstance != nullptr){
		delete this;
	}
	ptrInstance = this;

	//Wait for other classes to construct first, then load the file
	QTimer::singleShot(50, this, &ConfigManager::loadFile);

	qDebug() << "ConfigManager Constructed";
}

ConfigManager::~ConfigManager() {
	saveFile();
	qDebug() << "ConfigManager quit";
}

void ConfigManager::loadFile()
{
	QFile configFile("config.json");

	if(configFile.open(QIODevice::ReadOnly)){
		//Read data and turn it into a Json Doc
		QByteArray rawData = configFile.readAll();
		QJsonDocument jsonData(QJsonDocument::fromJson(rawData));

		//Tell any connected QObjects to read from the Json data
		emit read(jsonData.object());
	} else {
		qWarning("Unable to load file");
	}
}

void ConfigManager::saveFile()
{
	QFile configFile("config.json");

	if(configFile.open(QIODevice::WriteOnly)){
		QJsonObject jsonObj;

		//Tell any connected QObjects to insert their data into the Json Object
		emit write(jsonObj);

		//Write the Json Object to file
		configFile.write(QJsonDocument(jsonObj).toJson());
	} else {
		qWarning("Unable to save file");
	}
}
