#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>

/**
 * @brief Handles saving and loading data to JSON
 */
class ConfigManager : public QObject
{
	Q_OBJECT
public:
	explicit ConfigManager(QObject *parent = nullptr);
	~ConfigManager();

	//Singleton
	static ConfigManager* getInstance(){
		return ptrInstance;
	}

private slots:
	/**
	 * @brief Loads Json data from file.
	 */
	void loadFile();

private:

	//Singleton
	static ConfigManager* ptrInstance;

	/**
	 * @brief Saves Json data to file.
	 */
	void saveFile();

signals:
	void read(const QJsonObject &json);
	void write(QJsonObject &json);
};

#endif // CONFIGMANAGER_H
