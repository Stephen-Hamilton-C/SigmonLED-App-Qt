#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

/**
 * @brief Stores settings and handles saving and loading them with the ConfigManager.
 */
class Settings : public QObject
{
	Q_OBJECT

	Q_PROPERTY(bool darkMode MEMBER darkMode NOTIFY darkModeChanged)
	Q_PROPERTY(bool autoConnect MEMBER autoConnect NOTIFY autoConnectChanged)

public:
	explicit Settings(QObject *parent = nullptr);

	//Singleton
	static Settings* getInstance(){
		return ptrInstance;
	}

//Settings:
	/**
	 * @brief Dark Mode setting.
	 */
	bool darkMode = false;
	/**
	 * @brief Auto Connect setting, for reconnecting automatically to last device on boot.
	 */
	bool autoConnect = false;

private slots:
//ConfigManager:
	/**
	 * @brief Reads data from JSON.
	 * @param json The JSON file as an object.
	 */
	void read(const QJsonObject &json);
	/**
	 * @brief Writes data to the JSON object.
	 * @param json The JSON file as an object.
	 */
	void write(QJsonObject &json);

private:
	//Singleton
	static Settings* ptrInstance;

//Constants:
	/**
	 * @brief The Json key for the dark mode setting.
	 */
	const QString jsonDarkMode = "settings_DarkMode";
	/**
	 * @brief The Json key for the auto connect setting.
	 */
	const QString jsonAutoConn = "settings_AutoConnect";

signals:
	void darkModeChanged(bool darkMode);
	void autoConnectChanged(bool autoConnect);

};

#endif // SETTINGS_H
